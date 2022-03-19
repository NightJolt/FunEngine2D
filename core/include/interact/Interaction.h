#pragma once

#include "../Globals.h"
#include "../render/WindowManager.h"
#include "../ecs/ecs.h"

#include "Interactable.h"

namespace fun::interaction {
    void update();

    ecs::entity_t entity_at_pos(vec2f_t);
    bool is_anything_interacted();
}
