#include "ecs/ECS.h"
    
std::vector <fun::ecs::Entity> fun::ecs::entities = std::vector <Entity> ();

fun::ecs::EntityID fun::ecs::available = EntityID();
fun::ecs::Entity fun::ecs::next = NULLENTITY;

static fun::ecs::Entity entity_selected = fun::ecs::NULLENTITY;

std::vector <fun::ecs::dense_t> fun::ecs::denses = std::vector <dense_t> ();
std::vector <fun::ecs::sparse_t> fun::ecs::sparses = std::vector <sparse_t> ();
std::vector <std::any> fun::ecs::components = std::vector <std::any> ();
std::vector <size_t> fun::ecs::sizes = std::vector <size_t> ();

std::vector <std::any> fun::ecs::oncreate_callbacks = std::vector <std::any> ();
std::vector <std::any> fun::ecs::ondestroy_callbacks = std::vector <std::any> ();

fun::ecs::ComponentID fun::ecs::next_component_id = 0;

auto fun::ecs::get_entity_id(Entity entity) -> EntityID {
    return entity >> M_BITS(EntityV);
}

auto fun::ecs::get_entity_version(Entity entity) -> EntityV {
    return entity;
}

auto fun::ecs::generate_entity_uuid(EntityID id, EntityV version) -> Entity {
    return ((Entity)id << M_BITS(EntityV)) | version;
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

    if (entity_selected == entity) entity_selected = NULLENTITY; // ?

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
    return get_entity_id(entity) < entities.size() && entities[get_entity_id(entity)] == entity;
}

auto fun::ecs::is_id_alive(EntityID id) -> bool {
    return id < entities.size() && get_entity_id(entities[id]) == id;
}

auto fun::ecs::new_entity() -> Entity {
    if (available)
        return recycle_entity();
    else
        return create_entity();
}



// auto fun::ecs::show_hierarchy() -> void {
//     ImGui::Begin("Entities");
    
//     for (Entity entity : entities) {
//         if (!is_entity_alive(entity)) continue;

//         if (ImGui::Button(("ID: " + std::to_string(get_entity_id(entity)) + " | Ver: " + std::to_string(get_entity_version(entity))).c_str(), ImVec2(-FLT_MIN, 0.0f))) {
//             entity_selected = entity;
//         }
//     }

//     ImGui::End();
// }

// void fun::ecs::show_components() {
//     ImGui::Begin("Components");

//     if (entity_selected == NULLENTITY) {
//         ImGui::End();

//         return;
//     }
    
//     for (int i = 0; i < components.size(); i++) {
//         if (!has_component(entity_selected, i)) continue;

//         if (ImGui::Button(("ID: " + std::to_string(i)).c_str(), ImVec2(-FLT_MIN, 0.0f))) {}
//     }

//     ImGui::End();
// }