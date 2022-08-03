
#include "slime.cuh"

#include <windows.h>
#include <curand.h>
#include <curand_kernel.h>
#include <cuda_gl_interop.h>

#include <cstdio>





inline void check_err(cudaError_t result, char const *const func, int const line) {
	if (result) {
		fprintf(stderr, "CUDA error at line:%d code=%d(%s) \"%s\" \n", line,
			static_cast<unsigned int>(result), cudaGetErrorName(result), func);
		exit(EXIT_FAILURE);
	}
}

#define checkCudaErrors(val) check_err((val), #val, __LINE__)

bool fun::cuda::slime::check_cuda_devices() {
	int32_t n = 0;

	if (cudaGetDeviceCount(&n) != cudaError::cudaSuccess) {
		return false;
	}

	for (uint32_t i = 0; i < n; i++) {
		cudaDeviceProp properties;
		checkCudaErrors(cudaGetDeviceProperties(&properties, i));

		printf("#%u: %s\n", i, properties.name);
	}
    
	return n;
}





namespace {
    const uint32_t block_cnt = 1;
    const uint32_t block_dim = 1024;

    cudaGraphicsResource* canvas_res;
    cudaArray* canvas_arr;
}

void fun::cuda::slime::register_image(uint32_t image) {
    checkCudaErrors(cudaGraphicsGLRegisterImage(&::canvas_res, image, GL_TEXTURE_2D, cudaGraphicsRegisterFlagsSurfaceLoadStore));
}

void fun::cuda::slime::map_image() {
    checkCudaErrors(cudaGraphicsMapResources(1, &::canvas_res, 0));
    checkCudaErrors(cudaGraphicsSubResourceGetMappedArray(&::canvas_arr, ::canvas_res, 0, 0));
}

void fun::cuda::slime::unmap_image() {
    checkCudaErrors(cudaGraphicsUnmapResources(1, &::canvas_res, 0));
}




__device__ __inline__ uint32_t make_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    return r | g << 8 | b << 16 | a << 24;
}

__device__ __inline__ uint8_t get_alpha(uint32_t color) {
    return color >> 24;
}

__device__ __inline__ uint8_t get_blue(uint32_t color) {
    return color >> 16;
}

__device__ __inline__ uint8_t get_green(uint32_t color) {
    return color >> 8;
}

__device__ __inline__ uint8_t get_red(uint32_t color) {
    return color;
}



__device__ __inline__ uint32_t coord_to_index(uint32_t x, uint32_t y, uint32_t width) {
    return x + y * width;
}


__device__ __inline__ float radians(float degrees) {
    return degrees * 0.01745f;
}


namespace {
    float* value_map;
    float* temp_value_map;

    curandState* curand_states;

    uint32_t canvas_size_x;
    uint32_t canvas_size_y;

    uint32_t agent_count;

    struct agent_t {
        float pos_x, pos_y;
        float angle;
    };

    agent_t* agents;

    fun::cuda::slime::agent_specs_t* agent_specs;
    fun::cuda::slime::simulation_specs_t* simulation_specs;
}

__global__ void init_curand_states(curandState* curand_states, uint32_t seed, uint32_t block_dim) {
    for (uint32_t i = threadIdx.x; i < block_dim; i += blockDim.x) {
        curand_init(seed, i, 0, &curand_states[i]);
    }
}

__global__ void init_agents(::agent_t* agents, uint32_t count, uint32_t sx, uint32_t sy, curandState* curand_states) {
    for (uint32_t i = threadIdx.x; i < count; i += blockDim.x) {
        agents[i].pos_x = curand_uniform(&curand_states[threadIdx.x]) * (sx - 1);
        agents[i].pos_y = curand_uniform(&curand_states[threadIdx.x]) * (sy - 1);

        agents[i].angle = curand_uniform(&curand_states[threadIdx.x]) * 6.283f;
    }
}

void fun::cuda::slime::init_simulation(uint32_t canvas_size_x, uint32_t canvas_size_y, uint32_t seed, uint32_t agent_count, agent_specs_t* agent_specs, simulation_specs_t* simulation_specs) {
    ::canvas_size_x = canvas_size_x;
    ::canvas_size_y = canvas_size_y;
    ::agent_count = agent_count;
    ::agent_specs = agent_specs;
    ::simulation_specs = simulation_specs;

    checkCudaErrors(cudaMalloc(&::value_map, ::canvas_size_x * ::canvas_size_x * sizeof(float)));
    checkCudaErrors(cudaMalloc(&::temp_value_map, ::canvas_size_x * ::canvas_size_x * sizeof(float)));
    checkCudaErrors(cudaMalloc(&::curand_states, ::block_dim * sizeof curandState));
    checkCudaErrors(cudaMalloc(&::agents, ::agent_count * sizeof ::agent_t));

    cudaMemset(::value_map, 0, ::canvas_size_x * ::canvas_size_x * sizeof(float));

    init_curand_states <<<1, ::block_dim>>> (::curand_states, seed, ::block_dim);
    init_agents <<<1, ::block_dim>>> (::agents, ::agent_count, ::canvas_size_x, ::canvas_size_y, ::curand_states);
}

__global__ void step_move(float* value_map, uint32_t sx, uint32_t sy, ::agent_t* agents, uint32_t agent_count, fun::cuda::slime::agent_specs_t agent_specs, curandState* curand_states) {
    for (uint32_t i = threadIdx.x; i < agent_count; i += blockDim.x) {
        ::agent_t& agent = agents[i];

        float move_speed = agent_specs.move_speed;

        agent.pos_x += cos(agent.angle) * move_speed;
        agent.pos_y += sin(agent.angle) * move_speed;

        if (agent.pos_x < 0 || agent.pos_x >= sx || agent.pos_y < 0 || agent.pos_y >= sy) {
            agent.pos_x = max(0, min(sx - 1, (uint32_t)agent.pos_x));
            agent.pos_y = max(0, min(sy - 1, (uint32_t)agent.pos_y));

            agent.angle = curand_uniform(&curand_states[threadIdx.x]) * 6.283f;
        }

        value_map[coord_to_index((uint32_t)agents[i].pos_x, (uint32_t)agents[i].pos_y, sx)] = 1.f;
    }
}

__global__ void step_diffuse(float* value_map, float* temp_value_map, uint32_t sx, uint32_t sy, fun::cuda::slime::simulation_specs_t simulation_specs) {
    for (uint32_t i = threadIdx.x; i < sx * sy; i += blockDim.x) {
        float v = 0;
        
        for (int32_t x = -simulation_specs.diffuse_radius; x <= simulation_specs.diffuse_radius; x++) {
            for (int32_t y = -simulation_specs.diffuse_radius; y <= simulation_specs.diffuse_radius; y++) {
                int32_t nx = (i % sx) + x;
                int32_t ny = (i / sx) + y;

                if (nx >= 0 && nx < sx && ny >= 0 && ny < sy) {
                    v += value_map[coord_to_index(nx, ny, sx)];
                }
            }
        }
        
        v /= (simulation_specs.diffuse_radius * 2 + 1) * (simulation_specs.diffuse_radius * 2 + 1);

        temp_value_map[i] = value_map[i] + (v - value_map[i]) * simulation_specs.diffuse_speed;
    }
}

__global__ void step_decay(float* value_map, uint32_t sx, uint32_t sy, fun::cuda::slime::simulation_specs_t simulation_specs) {
    for (uint32_t i = threadIdx.x; i < sx * sy; i += blockDim.x) {
        value_map[i] = max(0.f, value_map[i] - simulation_specs.decay);
    }
}

__device__ float sense(float* value_map, uint32_t sx, uint32_t sy, ::agent_t& agent, fun::cuda::slime::agent_specs_t& agent_specs, float angle) {
    float v = 0;

    float sensor_angle = agent.angle + angle;

    float sensor_dir_x = cos(sensor_angle);
    float sensor_dir_y = sin(sensor_angle);

    float sensor_pos_x = agent.pos_x + sensor_dir_x * agent_specs.sensor_distance;
    float sensor_pos_y = agent.pos_y + sensor_dir_y * agent_specs.sensor_distance;

    for (int32_t x = -agent_specs.sensor_radius; x <= agent_specs.sensor_radius; x++) {
        for (int32_t y = -agent_specs.sensor_radius; y <= agent_specs.sensor_radius; y++) {
            int32_t nx = (int32_t)sensor_pos_x + x;
            int32_t ny = (int32_t)sensor_pos_y + y;

            if (nx >= 0 && nx < sx && ny >= 0 && ny < sy) {
                v += value_map[coord_to_index(nx, ny, sx)];
            }
        }
    }

    return v;
}

__global__ void step_sensor(float* value_map, uint32_t sx, uint32_t sy, ::agent_t* agents, uint32_t agent_count, fun::cuda::slime::agent_specs_t agent_specs, curandState* curand_states) {
    for (uint32_t i = threadIdx.x; i < agent_count; i += blockDim.x) {
        ::agent_t& agent = agents[i];

        float forward = sense(value_map, sx, sy, agent, agent_specs, 0);
        float right = sense(value_map, sx, sy, agent, agent_specs, agent_specs.sensor_angle);
        float left = sense(value_map, sx, sy, agent, agent_specs, -agent_specs.sensor_angle);

        float steer_strength = curand_uniform(&curand_states[threadIdx.x]);

        if (right > forward && left > forward) {
            agent.angle += (steer_strength * 2.f - 1.f) * agent_specs.turn_speed;
        } else if (left > right) {
            agent.angle -= steer_strength * agent_specs.turn_speed;
        } else if (right > left) {
            agent.angle += steer_strength * agent_specs.turn_speed;
        }
    }
}

__global__ void update_value_map(float* value_map, float* temp_value_map, uint32_t sx, uint32_t sy) {
    for (uint32_t i = threadIdx.x; i < sx * sy; i += blockDim.x) {
        value_map[i] = temp_value_map[i];
    }
}

__global__ void update_canvas(float* value_map, cudaSurfaceObject_t canvas, uint32_t sx, uint32_t sy) {
    for (uint32_t i = threadIdx.x; i < sx * sy; i += blockDim.x) {
        uint8_t v = value_map[i] * 255;
        uint32_t col = make_rgba(v, v, v, 255);

        surf2Dwrite(col, canvas, i % sx * sizeof uint32_t, i / sx);
    }
}

__global__ void color_canvas(float* value_map, cudaSurfaceObject_t canvas, uint32_t sx, uint32_t sy, uint8_t r, uint8_t g, uint8_t b, int32_t color_radius) {
    for (uint32_t i = threadIdx.x; i < sx * sy; i += blockDim.x) {
        float v = 0;

        for (int32_t x = -color_radius; x <= color_radius; x++) {
            for (int32_t y = -color_radius; y <= color_radius; y++) {
                int32_t nx = i % sx + x;
                int32_t ny = i / sx + y;

                if (nx >= 0 && nx < sx && ny >= 0 && ny < sy) {
                    v += value_map[coord_to_index(nx, ny, sx)];
                }
            }
        }

        const float max_val = (color_radius + .5f) * (color_radius + .5f);

        v = 1.f - abs(max_val - v) / max_val;

        uint32_t col = make_rgba(v * r, v * g, v * b, 255);
        
        surf2Dwrite(col, canvas, i % sx * sizeof uint32_t, i / sx);
    }
}

void fun::cuda::slime::step() {
    cudaResourceDesc description;
	memset(&description, 0, sizeof description);
    description.resType = cudaResourceTypeArray;
    description.res.array.array = ::canvas_arr;

    cudaSurfaceObject_t canvas;
    checkCudaErrors(cudaCreateSurfaceObject(&canvas, &description));

    step_move <<<1, ::block_dim>>> (::value_map, ::canvas_size_x, ::canvas_size_y, ::agents, ::agent_count, *::agent_specs, ::curand_states);
    step_diffuse <<<1, ::block_dim>>> (::value_map, ::temp_value_map, ::canvas_size_x, ::canvas_size_y, *::simulation_specs);
    update_value_map <<<1, ::block_dim>>> (::value_map, ::temp_value_map, ::canvas_size_x, ::canvas_size_y);
    step_decay <<<1, ::block_dim>>> (::value_map, ::canvas_size_x, ::canvas_size_y, *::simulation_specs);
    step_sensor <<<1, ::block_dim>>> (::value_map, ::canvas_size_x, ::canvas_size_y, ::agents, ::agent_count, *::agent_specs, ::curand_states);
    update_canvas <<<1, ::block_dim>>> (::value_map, canvas, ::canvas_size_x, ::canvas_size_y);
    // color_canvas <<<1, ::block_dim>>> (::value_map, canvas, ::canvas_size_x, ::canvas_size_y, ::simulation_specs->r, ::simulation_specs->g, ::simulation_specs->b, ::simulation_specs->color_radius);

    checkCudaErrors(cudaDeviceSynchronize());
    checkCudaErrors(cudaDestroySurfaceObject(canvas));
}