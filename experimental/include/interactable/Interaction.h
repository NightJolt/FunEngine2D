#pragma once

#include "../../../core/include/Globals.h"
#include "../../../core/include/render/WindowManager.h"
#include "../../../experimental/include/ecs/ECS.h"

#include "Interactable.h"

namespace fun::interaction {
    void update();

    Interactable* object_at_pos(sf::Vector2f);
    bool is_anything_interacted();
}
