#pragma once

#include "../globals.h"
#include "../render/window_manager.h"
#include "../ecs/ecs.h"
#include "../transform.h"
#include "interactable.h"

namespace fun::interaction {
    void update();

    ecs::entity_t entity_at_pos(vec2f_t);
    bool is_anything_interacted();

#if defined(DEBUG_BUILD)
    void display_debug_window();
#endif
}
