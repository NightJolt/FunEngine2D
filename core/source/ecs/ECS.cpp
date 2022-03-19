#include "ecs/ecs.h"
    
std::vector <fun::ecs::entity_t> fun::ecs::entities = std::vector <fun::ecs::entity_t> ();

fun::ecs::entity_id_t fun::ecs::available = fun::ecs::entity_id_t();
fun::ecs::entity_t fun::ecs::next = nullentity;

static fun::ecs::entity_t entity_selected = fun::ecs::nullentity;

std::vector <fun::ecs::dense_t> fun::ecs::denses = std::vector <dense_t> ();
std::vector <fun::ecs::sparse_t> fun::ecs::sparses = std::vector <sparse_t> ();
std::vector <std::any> fun::ecs::components = std::vector <std::any> ();
std::vector <uint32_t> fun::ecs::sizes = std::vector <uint32_t> ();

std::vector <std::any> fun::ecs::oncreate_callbacks = std::vector <std::any> ();
std::vector <std::any> fun::ecs::ondestroy_callbacks = std::vector <std::any> ();

fun::ecs::component_id_t fun::ecs::next_component_id = 0;

auto fun::ecs::get_entity_id(entity_t entity) -> entity_id_t {
    return entity >> BITS(entity_ver_t);
}

auto fun::ecs::get_entity_version(entity_t entity) -> entity_ver_t {
    return entity;
}

auto fun::ecs::generate_entity_uuid(entity_id_t id, entity_ver_t version) -> entity_t {
    return ((entity_t)id << BITS(entity_ver_t)) | version;
}

auto fun::ecs::create_entity() -> entity_t {
    return entities.emplace_back(generate_entity_uuid(entities.size(), 0));
}

auto fun::ecs::recycle_entity() -> entity_t {
    available--;

    entity_t entity = next;

    std::swap(next, entities[get_entity_id(next)]);

    return entity;
}

auto fun::ecs::destroy_entity(entity_t entity) -> void {
    if (!is_entity_alive(entity)) return;

    if (entity_selected == entity) entity_selected = nullentity; // ?

    entity_id_t id = get_entity_id(entity);

    entity++;

    entities[id] = entity;

    if (is_entity_recyclable(entity)) {
        std::swap(next, entities[id]);

        available++;
    }
}

auto fun::ecs::is_entity_recyclable(entity_t entity) -> bool {
    return ~(entity_ver_t)entity;
}

auto fun::ecs::is_entity_alive(entity_t entity) -> bool {
    return get_entity_id(entity) < entities.size() && entities[get_entity_id(entity)] == entity;
}

auto fun::ecs::is_id_alive(entity_id_t id) -> bool {
    return id < entities.size() && get_entity_id(entities[id]) == id;
}

auto fun::ecs::new_entity() -> entity_t {
    if (available)
        return recycle_entity();
    else
        return create_entity();
}

auto fun::ecs::validate_entity(entity_t entity) -> entity_t {
    return is_entity_alive(entity) ? entity : nullentity;
}



// auto fun::ecs::show_hierarchy() -> void {
//     ImGui::Begin("Entities");
    
//     for (entity_t entity : entities) {
//         if (!is_entity_alive(entity)) continue;

//         if (ImGui::Button(("ID: " + std::to_string(get_entity_id(entity)) + " | Ver: " + std::to_string(get_entity_version(entity))).c_str(), ImVec2(-FLT_MIN, 0.0f))) {
//             entity_selected = entity;
//         }
//     }

//     ImGui::End();
// }

// void fun::ecs::show_components() {
//     ImGui::Begin("Components");

//     if (entity_selected == nullentity) {
//         ImGui::End();

//         return;
//     }
    
//     for (int i = 0; i < components.size(); i++) {
//         if (!has_component(entity_selected, i)) continue;

//         if (ImGui::Button(("ID: " + std::to_string(i)).c_str(), ImVec2(-FLT_MIN, 0.0f))) {}
//     }

//     ImGui::End();
// }