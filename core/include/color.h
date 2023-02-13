#pragma once

#include "globals.h"

// todos
// - add more colors
// - add more color formats
// - add palettes

namespace fun {
    struct rgb_t;
    struct rgba_t;

    struct rgb_t {
        static const rgb_t black;
        static const rgb_t white;
        static const rgb_t red;
        static const rgb_t green;
        static const rgb_t blue;

        rgb_t();
        rgb_t(uint8_t, uint8_t, uint8_t);
        rgb_t(const rgba_t&);

        rgb_t invert() const;

        uint8_t r;
        uint8_t g;
        uint8_t b;

        bool operator ==(const rgb_t&) const;

        static rgb_t from_float(float, float, float);
        std::array <float, 3> to_float() const;

#if defined(FE2D_SFML)
        rgb_t(sf::Color);
        sf::Color to_sf() const;
#endif

        std::string to_str() const;
    };

    struct rgba_t {
        static const rgba_t black;
        static const rgba_t white;
        static const rgba_t transparent;

        rgba_t();
        rgba_t(uint8_t, uint8_t, uint8_t, uint8_t);
        rgba_t(const rgb_t&);
        rgba_t(const rgb_t&, uint8_t);

        rgba_t invert() const;

        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;

        bool operator ==(const rgba_t&) const;

        static rgba_t from_float(float, float, float, float);
        std::array <float, 4> to_float() const;

#if defined(FE2D_SFML)
        rgba_t(sf::Color);
        sf::Color to_sf() const;
#endif

        std::string to_str() const;
    };
}