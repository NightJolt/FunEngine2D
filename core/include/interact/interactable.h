#pragma once

#include "../globals.h"
#include "../vec2.h"

namespace fun {
    struct interact_result_t {
        bool interacted;
        vec2f_t offset;
    };

    struct interactable_t {
        explicit interactable_t(const std::function <interact_result_t(vec2f_t, vec2f_t)>&, layer_t = 0);

        void set_layer(layer_t);

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

        std::function <interact_result_t(vec2f_t, vec2f_t)> interaction_fun;
    };
}
