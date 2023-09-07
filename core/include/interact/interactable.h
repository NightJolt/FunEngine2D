#pragma once

#include "../globals.h"
#include "../vec2.h"
#include "../ecs/ecs.h"

namespace fun {
    struct interact_result_t {
        bool interacted;
    };

    enum interact_event_t {
        right_pressed,
        right_hold,
        right_released,

        left_pressed,
        left_hold,
        left_released,

        hover_enter,
        hover_hold,
        hover_exit,
    };

    struct interact_data_t {
        interact_event_t event;
    };

    // * not passing entity because handler function will not always use it. for performance sake it can just capture it
    typedef std::function <interact_result_t(vec2f_t world_pos, vec2f_t screen_pos)> interact_fun_t;
    typedef std::function <void(ecs::entity_t, interact_data_t)> action_fun_t;

    struct interactable_t {
        explicit interactable_t(const interact_fun_t&, const action_fun_t&, layer_t = 0);

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

        layer_t layer;

        interact_fun_t interaction_fun;
        action_fun_t action_fun;
    };
}
