#pragma once

#include "../../../core/include/globals.h"

namespace fun::physics {
    extern b2Vec2 gravity;
    extern b2World world;

    void set_gravity(b2Vec2);
    void simulate();
}