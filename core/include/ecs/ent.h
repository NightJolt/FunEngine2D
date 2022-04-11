#pragma once

#include "../globals.h"
#include "ecs.h"
#include "../transform.h"

namespace fun::ent {
    fun::ecs::entity_t create_empty(); // no components
    fun::ecs::entity_t create_basic(); // transform
}