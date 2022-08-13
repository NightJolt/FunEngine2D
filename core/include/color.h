#pragma once

#include "globals.h"

namespace fun {
    struct rgb_t;
    struct rgba_t;

    struct rgb_t {
        static const rgb_t black;
        static const rgb_t white;

        rgb_t();
        rgb_t(uint8_t, uint8_t, uint8_t);
        rgb_t(const rgba_t&);

        uint8_t r;
        uint8_t g;
        uint8_t b;

        bool operator ==(const rgb_t&) const;

        static rgb_t from_float(float, float, float);
        std::array <float, 3> to_float() const;

#if defined(USES_SFML)
        rgb_t(sf::Color);
        sf::Color to_sf() const;
#endif

        std::string to_str() const;
    };

    struct rgba_t {
        static const rgba_t black;
        static const rgba_t white;

        rgba_t();
        rgba_t(uint8_t, uint8_t, uint8_t, uint8_t);
        rgba_t(const rgb_t&);
        rgba_t(const rgb_t&, uint8_t);

        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;

        bool operator ==(const rgba_t&) const;

        static rgba_t from_float(float, float, float, float);
        std::array <float, 4> to_float() const;

#if defined(USES_SFML)
        rgba_t(sf::Color);
        sf::Color to_sf() const;
#endif

        std::string to_str() const;
    };
}