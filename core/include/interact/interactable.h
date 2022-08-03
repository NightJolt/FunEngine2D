#pragma once

#include "../globals.h"
#include "../_math.h"
#include "../input.h"

namespace fun {
    struct interactable_t {
        explicit interactable_t(const std::function <bool(vec2f_t)>&, layer_t = 0);

        bool right_pressed;
        bool right_hold;
        bool right_released;

        bool left_pressed;
        bool left_hold;
        bool left_released;

        bool hover_enter;
        bool hover_hold;
        bool hover_exit;

        vec2f_t mouse_left_offset;
        vec2f_t mouse_right_offset;

        layer_t layer;

        std::function <bool(vec2f_t)> interaction_fun;
    };
}
