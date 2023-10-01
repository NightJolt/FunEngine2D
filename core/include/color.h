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
        rgb_t();
        constexpr rgb_t(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b) {}
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
        operator sf::Color() const;
#endif

        std::string to_str() const;

        static rgb_t rand();
        static rgb_t rand_grayscale();
    };

	namespace rgb {
		inline constexpr rgb_t black = { 0, 0, 0 };
		inline constexpr rgb_t white = { 255, 255, 255 };
		inline constexpr rgb_t red = { 255, 0, 0 };
		inline constexpr rgb_t green = { 0, 255, 0 };
		inline constexpr rgb_t blue = { 0, 0, 255 };
	}

    typedef std::array <rgb_t, 4> rgb_t4;

    struct rgba_t {
        rgba_t();
        constexpr rgba_t(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : r(r), g(g), b(b), a(a) {};
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
        operator sf::Color() const;
#endif

        std::string to_str() const;
    };

	namespace rgba {
		inline constexpr rgba_t black = { 0, 0, 0, 255 };
		inline constexpr rgba_t white = { 255, 255, 255, 255 };
		inline constexpr rgba_t red = { 255, 0, 0, 255 };
		inline constexpr rgba_t green = { 0, 255, 0, 255 };
		inline constexpr rgba_t blue = { 0, 0, 255, 255 };
		inline constexpr rgba_t transparent = { 0, 0, 0, 0 };
	}

    typedef std::array <rgba_t, 4> rgba_t4;
}