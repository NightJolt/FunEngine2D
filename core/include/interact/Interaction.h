#pragma once

#include "../globals.h"
#include "../render/window_manager.h"
#include "../ecs/ecs.h"
#include "interactable.h"

namespace fun::interaction {
    void update();

    ecs::entity_t entity_at_pos(vec2f_t);
    bool is_anything_interacted();
}
