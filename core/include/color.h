#pragma once

#include "globals.h"

namespace fun {
    struct rgb_t {
        rgb_t() : r(0), g(0), b(0) {}
        rgb_t(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b) {}

        uint8_t r;
        uint8_t g;
        uint8_t b;
    };
}