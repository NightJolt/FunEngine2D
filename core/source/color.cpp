#include "color.h"

#pragma region rgb_t
const fun::rgb_t fun::rgb_t::black = { 0, 0, 0 };
const fun::rgb_t fun::rgb_t::white = { 255, 255, 255 };
const fun::rgb_t fun::rgb_t::red = { 255, 0, 0 };
const fun::rgb_t fun::rgb_t::green = { 0, 255, 0 };
const fun::rgb_t fun::rgb_t::blue = { 0, 0, 255 };

fun::rgb_t::rgb_t() : r(0), g(0), b(0) {}
fun::rgb_t::rgb_t(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b) {}
fun::rgb_t::rgb_t(const rgba_t& rgba) : r(rgba.r), g(rgba.g), b(rgba.b) {}

fun::rgb_t fun::rgb_t::invert() const {
    return { 255u - r, 255u - g, 255u - b };
}

bool fun::rgb_t::operator ==(const rgb_t& other) const {
    return r == other.r && g == other.g && b == other.b;
}

fun::rgb_t fun::rgb_t::from_float(float r, float g, float b) {
    return { (uint8_t)(r * 255), (uint8_t)(g * 255), (uint8_t)(b * 255) };
}

std::array <float, 3> fun::rgb_t::to_float() const {
    return { (float)r / 255.f, (float)g / 255.f, (float)b / 255.f };
}

#if defined(FE2D_SFML)
fun::rgb_t::rgb_t(sf::Color color) : r(color.r), g(color.g), b(color.b) {}

sf::Color fun::rgb_t::to_sf() const {
    return sf::Color(r, g, b);
}
#endif

std::string fun::rgb_t::to_str() const {
    return "rgb(" + std::to_string(r) + ", " + std::to_string(g) + ", " + std::to_string(b) + ")";
}
#pragma endregion

#pragma region rgba_t
const fun::rgba_t fun::rgba_t::black = { 0, 0, 0, 255 };
const fun::rgba_t fun::rgba_t::white = { 255, 255, 255, 255 };
const fun::rgba_t fun::rgba_t::transparent = { 0, 0, 0, 0 };

fun::rgba_t::rgba_t() : r(0), g(0), b(0), a(255) {}
fun::rgba_t::rgba_t(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : r(r), g(g), b(b), a(a) {}
fun::rgba_t::rgba_t(const rgb_t& rgb) : r(rgb.r), g(rgb.g), b(rgb.b), a(255) {}
fun::rgba_t::rgba_t(const rgb_t& rgb, uint8_t a) : r(rgb.r), g(rgb.g), b(rgb.b), a(a) {}

fun::rgba_t fun::rgba_t::invert() const {
    return { 255u - r, 255u - g, 255u - b, a };
}

bool fun::rgba_t::operator ==(const rgba_t& other) const {
    return r == other.r && g == other.g && b == other.b && a == other.a;
}

fun::rgba_t fun::rgba_t::from_float(float r, float g, float b, float a) {
    return { (uint8_t)(r * 255), (uint8_t)(g * 255), (uint8_t)(b * 255), (uint8_t)(a * 255) };
}

std::array <float, 4> fun::rgba_t::to_float() const {
    return { (float)r / 255.f, (float)g / 255.f, (float)b / 255.f, (float)a / 255.f };
}

#if defined(FE2D_SFML)
fun::rgba_t::rgba_t(sf::Color color) : r(color.r), g(color.g), b(color.b), a(color.a) {}

sf::Color fun::rgba_t::to_sf() const {
    return sf::Color(r, g, b, a);
}
#endif

std::string fun::rgba_t::to_str() const {
    return "rgba(" + std::to_string(r) + ", " + std::to_string(g) + ", " + std::to_string(b) + ", " + std::to_string(a) + ")";
}
#pragma endregion