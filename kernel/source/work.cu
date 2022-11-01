#include "work.cuh"

#include <stdio.h>

inline void check_err(cudaError_t result, char const *const func, int const line) {
	if (result) {
		fprintf(stderr, "CUDA error at line:%d code=%d(%s) \"%s\" \n", line, static_cast<unsigned int>(result), cudaGetErrorName(result), func);

		exit(EXIT_FAILURE);
	}
}

#define checkCudaErrors(val) check_err((val), #val, __LINE__)




__host__ void create_texture(color_t** texture, uint32_t width, uint32_t height) {
    checkCudaErrors(cudaMalloc(texture, width * height * sizeof(color_t)));
}

__host__ void free_texture(color_t* texture) {
    checkCudaErrors(cudaFree(texture));
}





__global__ void cuda_fill_texture(color_t* texture, uint32_t width, uint32_t height, color_t color) {
    uint32_t ind = blockIdx.x * blockDim.x + threadIdx.x;
    const uint32_t stride = blockDim.x * gridDim.x;
    const uint32_t size = width * height;
    
    for (uint32_t i = ind; i < size; i += stride) {
        texture[i] = color;
    }
}

__host__ void fill_texture(color_t* texture, uint32_t width, uint32_t height, color_t color) {
    cuda_fill_texture <<<256, 256>>> (texture, width, height, color);
}



void create_surface(color_t** surface, uint32_t width, uint32_t height) {
    *surface = (color_t*)malloc(width * height * sizeof(color_t));
}

void free_surface(color_t* surface) {
    free(surface);
}




__host__ void texture_to_surface(color_t* surface, color_t* texture, uint32_t width, uint32_t height) {
    checkCudaErrors(cudaMemcpy(surface, texture, width * height * sizeof(color_t), cudaMemcpyDeviceToHost));
}

__host__ void surface_to_texture(color_t* texture, color_t* surface, uint32_t width, uint32_t height) {
    checkCudaErrors(cudaMemcpy(texture, surface, width * height * sizeof(color_t), cudaMemcpyHostToDevice));
}



__global__ void cuda_blit_texture(
    color_t* target_texture,
    color_t* source_texture,
    channel_t* mask,
    uint32_t target_x,
    uint32_t target_y,
    uint32_t target_w,
    uint32_t target_h,
    uint32_t source_x,
    uint32_t source_y,
    uint32_t source_w,
    uint32_t source_h
) {
    uint32_t ind = blockIdx.x * blockDim.x + threadIdx.x;
    const uint32_t stride = blockDim.x * gridDim.x;
    const uint32_t size = target_w * target_h;
    
    for (uint32_t i = ind; i < size; i += stride) {
        uint32_t tx = i % target_w;
        uint32_t ty = i / target_w;
        
        uint32_t sx = (float)(tx - target_x) / target_w * source_w + source_x;
        uint32_t sy = (float)(ty - target_y) / target_h * source_h + source_h;

        uint32_t source_ind = sy * source_w + sx;
        
        if (mask && mask[source_ind] == 0) {
            continue;
        }
    }
}

__host__ void blit_texture(
    color_t* target_texture,
    color_t* source_texture,
    channel_t* mask,
    uint32_t target_x,
    uint32_t target_y,
    uint32_t target_w,
    uint32_t target_h,
    uint32_t source_x,
    uint32_t source_y,
    uint32_t source_w,
    uint32_t source_h
) {
    cuda_blit_texture <<<256, 256>>> (
        target_texture,
        source_texture,
        mask,
        target_x,
        target_y,
        target_w,
        target_h,
        source_x,
        source_y,
        source_w,
        source_h
    );
}