#include "color.h"

const fun::rgb_t fun::rgb_t::black = { 0, 0, 0 };
const fun::rgb_t fun::rgb_t::white = { 255, 255, 255 };

fun::rgb_t::rgb_t() : r(0), g(0), b(0) {}
fun::rgb_t::rgb_t(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b) {}

bool fun::rgb_t::operator ==(const rgb_t& other) const {
    return r == other.r && g == other.g && b == other.b;
}

fun::rgb_t fun::rgb_t::from_float(float r, float g, float b) {
    return { (uint8_t)(r * 255), (uint8_t)(g * 255), (uint8_t)(b * 255) };
}

std::array <float, 3> fun::rgb_t::to_float() const {
    return { (float)r / 255.f, (float)g / 255.f, (float)b / 255.f };
}

#if defined(USES_SFML)
fun::rgb_t::rgb_t(sf::Color color) : r(color.r), g(color.g), b(color.b) {}

sf::Color fun::rgb_t::to_sf() const {
    return sf::Color(r, g, b);
}
#endif

std::string fun::rgb_t::to_str() const {
    return "rgb(" + std::to_string(r) + ", " + std::to_string(g) + ", " + std::to_string(b) + ")";
}
