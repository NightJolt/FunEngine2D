#pragma once

#include "../../../core/include/globals.h"
#include "../../../core/include/_Time.h"

namespace fun::physics {
    void set_gravity(b2Vec2);
    void set_timestep(float);
    void set_velocity_iterations(uint8_t);
    void set_position_iterations(uint8_t);

    void simulate();

    // void clear();
}