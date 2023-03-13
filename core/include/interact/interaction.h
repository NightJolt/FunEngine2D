#pragma once

#include "../globals.h"
#include "../ecs/ecs.h"
#include "../vec2.h"

namespace fun::interaction {
    void update();

    ecs::entity_t entity_at_pos(vec2f_t, vec2f_t);
    bool is_anything_interacted();
    
    void display_debug_window();
}
