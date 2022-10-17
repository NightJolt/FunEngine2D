#pragma once

#include "../../globals.h"
#include "../../vec2.h"

namespace fun::render {
    struct window_data_t {
        explicit window_data_t(const std::string& = "unnamed", const vec2u_t = { 856, 482 }, fun::mask32_t = sf::Style::Default, const sf::ContextSettings& = sf::ContextSettings());

        std::string name;
        vec2u_t size;
        fun::mask32_t style;
        sf::ContextSettings settings;
    };
}