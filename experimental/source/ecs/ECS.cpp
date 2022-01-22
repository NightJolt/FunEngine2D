#include "ecs/ECS.h"

static std::vector <fun::ecs::Entity> entities;

static fun::ecs::EntityID available;
static fun::ecs::Entity next = -1;

static std::vector <std::vector <fun::ecs::EntityV>> denses = std::vector <std::vector <fun::ecs::EntityV>> ();
static std::vector <std::vector <fun::ecs::EntityID>> sparses = std::vector <std::vector <fun::ecs::EntityID>> ();
static std::vector <std::vector <uint8_t>> components = std::vector <std::vector <uint8_t>> ();
static std::vector <uint32_t> sizes = std::vector <uint32_t> ();



auto fun::ecs::get_entity_id(Entity entity) -> EntityID {
    return entity >> bits(EntityV);
}

auto fun::ecs::get_entity_version(Entity entity) -> EntityV {
    return entity;
}



auto fun::ecs::generate_entity_uuid(EntityID id, EntityV version) -> Entity {
    return ((Entity)id << bits(EntityV)) | version;
}

auto fun::ecs::create_entity() -> Entity {
    return entities.emplace_back(generate_entity_uuid(entities.size(), 0));
}

auto fun::ecs::recycle_entity() -> Entity {
    available--;

    Entity entity = next;

    std::swap(next, entities[get_entity_id(next)]);

    return entity;
}

auto fun::ecs::destroy_entity(Entity entity) -> void {
    if (!is_entity_alive(entity)) return;

    EntityID id = get_entity_id(entity);

    entity++;

    entities[id] = entity;

    if (is_entity_recyclable(entity)) {
        std::swap(next, entities[id]);

        available++;
    }
}

auto fun::ecs::is_entity_recyclable(Entity entity) -> bool {
    return ~(EntityV)entity;
}



auto fun::ecs::is_entity_alive(Entity entity) -> bool {
    return entities[get_entity_id(entity)] == entity;
}

auto fun::ecs::is_id_alive(EntityID id) -> bool {
    return get_entity_id(entities[id]) == id;
}

auto fun::ecs::new_entity() -> Entity {
    if (available)
        return recycle_entity();
    else
        return create_entity();
}



auto fun::ecs::show_hierarchy() -> void {
    ImGui::Begin("Entities");

    EntityID id = -1;
    
    for (Entity entity : entities) {
        if (!is_id_alive(++id)) continue;

        if (ImGui::Button(("ID: " + std::to_string(get_entity_id(entity)) + " | Ver: " + std::to_string(get_entity_version(entity))).c_str(), ImVec2(-FLT_MIN, 0.0f))) {}
    }

    ImGui::End();
}