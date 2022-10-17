#pragma once

#include "../globals.h"
#include "ecs/ecs.h"

namespace fun::ent {
    fun::ecs::entity_t create_empty(); // no components
    fun::ecs::entity_t create_basic(); // transform
}