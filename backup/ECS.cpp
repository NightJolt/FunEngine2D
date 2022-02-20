#include "ecs/ECS.h"

#define NULLENTITY -1
#define NULLADDR -1

static std::vector <fun::ecs::Entity> entities;

static fun::ecs::EntityID available;
static fun::ecs::Entity next = NULLENTITY;

fun::ecs::ComponentID fun::ecs::next_component_id = 0;

typedef std::vector <fun::ecs::Entity> dense_t;
typedef std::vector <size_t> sparse_t;
typedef std::vector <uint8_t> components_t;

static std::vector <dense_t> denses;
static std::vector <sparse_t> sparses;
static std::vector <components_t> components;
static std::vector <size_t> sizes;

static fun::ecs::Entity entity_selected = NULLENTITY;



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

    if (entity_selected == entity) entity_selected = NULLENTITY;

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



auto fun::ecs::show_hierarchy() -> void {
    ImGui::Begin("Entities");
    
    for (Entity entity : entities) {
        if (!is_entity_alive(entity)) continue;

        if (ImGui::Button(("ID: " + std::to_string(get_entity_id(entity)) + " | Ver: " + std::to_string(get_entity_version(entity))).c_str(), ImVec2(-FLT_MIN, 0.0f))) {
            entity_selected = entity;
        }
    }

    ImGui::End();
}



components_t* fun::ecs::get_component_array(ComponentID component_id) {
    return &components[component_id];
}

dense_t* fun::ecs::get_entities_array(ComponentID component_id){
    return &denses[component_id];
}

bool fun::ecs::has_component(Entity entity, ComponentID component_id) {
    if (!is_entity_alive(entity) || sizes.size() <= component_id) return false;

    EntityID entity_id = get_entity_id(entity);
    EntityV entity_v = get_entity_version(entity);

    auto* dense = &denses[component_id];
    auto* sparse = &sparses[component_id];
    
    if (sparse->size() <= entity_id) return false;

    auto dense_index = (*sparse)[entity_id];

    if (sizes[component_id] <= dense_index) return false;

    return get_entity_version((*dense)[dense_index]) == entity_v;
}

void fun::ecs::add_component(Entity entity, ComponentID component_id, size_t component_size, std::function <void(uint8_t*)> create_component) {
    if (sizes.size() <= component_id) {
        auto new_size = component_id + 1;

        denses.resize(new_size, dense_t());
        sparses.resize(new_size, sparse_t());
        components.resize(new_size, components_t());
        sizes.resize(new_size, 0);
    }

    EntityID entity_id = get_entity_id(entity);
    EntityID entity_v = get_entity_version(entity);

    auto* dense = &denses[component_id];
    auto* sparse = &sparses[component_id];
    auto* t_componets = &components[component_id];
    auto* size_p = &sizes[component_id];
    auto size = *size_p;
    
    {
        if (dense->size() == size) {
            dense->emplace_back(entity);
        } else {
            (*dense)[size] = entity;
        }

        (*size_p)++;
    }

    {
        if (sparse->size() <= entity_id) {
            sparse->resize(entity_id + 1, NULLADDR);
        }

        (*sparse)[entity_id] = size;
    }

    {
        size_t length = size * component_size;
        size_t arr_length = t_componets->size();

        if (arr_length <= length) {
            t_componets->resize(arr_length + component_size);
        }

        create_component(&(*t_componets)[length]);
    }
}

uint8_t* fun::ecs::get_component(Entity entity, ComponentID component_id, size_t component_size) {
    return &components[component_id][component_size * sparses[component_id][get_entity_id(entity)]];
}

void fun::ecs::remove_component(Entity entity, ComponentID component_id, size_t component_size) {
    auto* dense = &denses[component_id];
    auto* sparse = &sparses[component_id];
    auto* t_componets = &components[component_id];
    auto size = --sizes[component_id];

    EntityID entity_id = get_entity_id(entity);
    EntityV entity_v = get_entity_version(entity);
    size_t entity_ind = (*sparse)[entity_id];

    if (entity_ind == size) return;

    Entity other = (*dense)[size];

    EntityID other_id = get_entity_id(other);
    EntityV other_v = get_entity_version(other);
    size_t other_ind = (*sparse)[other_id];

    {
        std::swap((*dense)[entity_ind], (*dense)[other_ind]);

        (*sparse)[entity_id] = NULLADDR;
        (*sparse)[other_id] = entity_ind;
    }

    {
        uint8_t* entity_component = &(*t_componets)[entity_ind * component_size];
        uint8_t* other_component = &(*t_componets)[other_ind * component_size];

        std::memcpy(entity_component, other_component, component_size);
    }
}

void fun::ecs::show_components() {
    ImGui::Begin("Components");

    if (entity_selected == NULLENTITY) {
        ImGui::End();

        return;
    }
    
    for (int i = 0; i < components.size(); i++) {
        if (!has_component(entity_selected, i)) continue;

        if (ImGui::Button(("ID: " + std::to_string(i)).c_str(), ImVec2(-FLT_MIN, 0.0f))) {}
    }

    ImGui::End();
}