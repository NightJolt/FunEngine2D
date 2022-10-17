#pragma once

#include "../globals.h"
#include "../vec2.h"

namespace fun::physics {
    void set_simulation_scale(float);
    float get_simulation_scale();

    void set_gravity(vec2f_t);
    void set_timestep(float);
    void set_velocity_iterations(uint8_t);
    void set_position_iterations(uint8_t);

    void simulate();

    b2Body* create_body(const b2BodyDef&);
    void destroy_body(b2Body*);

    // void clear();
}
