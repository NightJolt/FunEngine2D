#include "ecs/ent.h"
#include "transform.h"

fun::ecs::entity_t fun::ent::create_empty() {
    return ecs::new_entity();
}

fun::ecs::entity_t fun::ent::create_basic() {
    auto entity = create_empty();

    ecs::add_component <transform_t> (entity);

    return entity;
}