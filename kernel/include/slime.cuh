#pragma once

#include <cstdint>

namespace fun::cuda::slime {
    bool check_cuda_devices();

    void register_image(uint32_t);
    void map_image();
    void unmap_image();

    struct agent_specs_t {
        float move_speed;
        float turn_speed;
        float sensor_distance;
        int32_t sensor_radius;
        float sensor_angle;
    };

    struct simulation_specs_t {
        uint8_t r, g, b;
        int32_t color_radius;
        int32_t diffuse_radius;
        float diffuse_speed;
        float decay;
    };

    void init_simulation(uint32_t, uint32_t, uint32_t, uint32_t, agent_specs_t*, simulation_specs_t*);
    void step();
}