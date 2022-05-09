#include "color.h"

fun::rgb_t::rgb_t() : r(0), g(0), b(0) {}
fun::rgb_t::rgb_t(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b) {}

#if defined(USES_SFML)
fun::rgb_t::rgb_t(sf::Color color) : r(color.r), g(color.g), b(color.b) {}

sf::Color fun::rgb_t::to_sf() const {
    return sf::Color(r, g, b);
}
#endif

std::string fun::rgb_t::to_str() const {
    return "rgb(" + std::to_string(r) + ", " + std::to_string(g) + ", " + std::to_string(b) + ")";
}
