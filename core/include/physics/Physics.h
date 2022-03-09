#pragma once

#include "../Globals.h"
#include "../_Time.h"

namespace fun::physics {
    void set_simulation_scale(float);
    float get_simulation_scale();

    void set_gravity(b2Vec2);
    void set_timestep(float);
    void set_velocity_iterations(uint8_t);
    void set_position_iterations(uint8_t);

    void simulate();

    b2Body* create_body(const b2BodyDef&);
    void destroy_body(b2Body*);

    // void clear();
}