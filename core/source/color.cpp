#include "color.h"

#include <_math.h>

#pragma region rgb_t
fun::rgb_t::rgb_t() : r(0), g(0), b(0) {}
fun::rgb_t::rgb_t(const rgba_t& rgba) : r(rgba.r), g(rgba.g), b(rgba.b) {}

fun::rgb_t fun::rgb_t::invert() const {
    return { uint8_t(255u - r), (uint8_t)(255u - g), (uint8_t)(255u - b) };
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

fun::rgb_t::operator sf::Color() const {
    return to_sf();
}
#endif

std::string fun::rgb_t::to_str() const {
    return "rgb(" + std::to_string(r) + ", " + std::to_string(g) + ", " + std::to_string(b) + ")";
}

fun::rgb_t fun::rgb_t::rand() {
    uint32_t val = math::random_32(0, 255 * 255 * 255);

    return { (uint8_t)(val >> 16), (uint8_t)(val >> 8), (uint8_t)val };
}

fun::rgb_t fun::rgb_t::rand_grayscale() {
    uint8_t val = math::random_32(0, 255);

    return { val, val, val };
}
#pragma endregion

#pragma region rgba_t
fun::rgba_t::rgba_t() : r(0), g(0), b(0), a(255) {}
fun::rgba_t::rgba_t(const rgb_t& rgb) : r(rgb.r), g(rgb.g), b(rgb.b), a(255) {}
fun::rgba_t::rgba_t(const rgb_t& rgb, uint8_t a) : r(rgb.r), g(rgb.g), b(rgb.b), a(a) {}

fun::rgba_t fun::rgba_t::invert() const {
    return { uint8_t(255u - r), uint8_t(255u - g), uint8_t(255u - b), a };
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

fun::rgba_t::operator sf::Color() const {
    return to_sf();
}
#endif

std::string fun::rgba_t::to_str() const {
    return "rgba(" + std::to_string(r) + ", " + std::to_string(g) + ", " + std::to_string(b) + ", " + std::to_string(a) + ")";
}
#pragma endregion