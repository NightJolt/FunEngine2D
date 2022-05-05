#pragma once

#include "globals.h"

namespace fun {
    struct rgb_t {
        rgb_t();
        rgb_t(uint8_t, uint8_t, uint8_t);

        uint8_t r;
        uint8_t g;
        uint8_t b;

#if defined(USES_SFML)
        rgb_t(sf::Color);
        sf::Color to_sf() const;
#endif
    };
}