#pragma once

template <class T>
auto fun::ecs::get_component_id() -> ComponentID {
    static ComponentID id = next_component_id++;

    return id;
}

// template <class T>
// auto fun::ecs::get_entities() -> std::vector <Entity>& {
//     return denses[get_component_id <T> ()];
// }

template <class T>
auto fun::ecs::does_component_exist() -> bool {
    const ComponentID component_id = get_component_id <T> ();

    return components.size() > component_id && components[component_id].has_value();
}

template <class T>
auto fun::ecs::iterate_component() -> ComponentIterator <T> {
    const ComponentID component_id = get_component_id <T> ();

    return ComponentIterator <T> (std::any_cast <std::vector <T>&> (components[component_id]), sizes[component_id]);
}

template <class T>
auto fun::ecs::get_component_array() -> std::vector <T>& {
    return std::any_cast <std::vector <T>&> (components[get_component_id <T> ()]);
}

template <class T>
auto fun::ecs::get_component(Entity entity) -> T& {
    return get_component_array <T> ()[sparses[get_component_id <T> ()][get_entity_id(entity)]];
}

template <class T>
auto fun::ecs::has_component(Entity entity) -> bool {
    const ComponentID component_id = get_component_id <T> ();

    if (!is_entity_alive(entity) || sizes.size() <= component_id) return false;

    EntityID entity_id = get_entity_id(entity);
    EntityV entity_v = get_entity_version(entity);

    auto& dense = denses[component_id];
    auto& sparse = sparses[component_id];
    
    if (sparse.size() <= entity_id) return false;

    auto dense_index = sparse[entity_id];

    if (sizes[component_id] <= dense_index) return false;

    return get_entity_version(dense[dense_index]) == entity_v;
}

template <class T, class... Args>
auto fun::ecs::add_component(Entity entity, Args&&... args) -> void {
    const ComponentID component_id = get_component_id <T> ();

    if (sizes.size() <= component_id) {
        auto new_size = component_id + 1;

        denses.resize(new_size, dense_t());
        sparses.resize(new_size, sparse_t());
        components.resize(new_size);
        sizes.resize(new_size, 0);
    }

    EntityID entity_id = get_entity_id(entity);
    EntityID entity_v = get_entity_version(entity);

    if (!components[component_id].has_value()) {
        components[component_id] = std::vector <T> ();
    }

    auto& dense = denses[component_id];
    auto& sparse = sparses[component_id];
    auto& component_arr = std::any_cast <std::vector <T>&> (components[component_id]);
    auto& size_p = sizes[component_id];
    auto size = size_p;
    
    {
        if (dense.size() == size) {
            dense.emplace_back(entity);
        } else {
            dense[size] = entity;
        }

        size_p++;
    }

    {
        if (sparse.size() <= entity_id) {
            sparse.resize(entity_id + 1, NULLADDR);
        }

        sparse[entity_id] = size;
    }

    {
        size_t arr_size = component_arr.size();

        if (arr_size == size) {
            component_arr.reserve(arr_size + 1);
            component_arr.emplace_back(std::forward <Args> (args)...);
        } else {
            component_arr[size] = T(std::forward <Args> (args)...);
        }

        if (oncreate_callbacks.size() > component_id) {
            auto& callback_any = oncreate_callbacks[component_id];

            if (callback_any.has_value()) {
                auto& callback = std::any_cast <std::function <void(T&)>&> (callback_any);

                callback(component_arr[size]);
            } 
        }
    }
}

template <class T>
auto fun::ecs::remove_component(Entity entity) -> void {
    const ComponentID component_id = get_component_id <T> ();
    
    auto size = --sizes[component_id];
    
    EntityID entity_id = get_entity_id(entity);
    auto& sparse = sparses[component_id];
    auto entity_ind = sparse[entity_id];

    if (entity_ind == size) return;

    auto& dense = denses[component_id];
    auto& component_arr = std::any_cast <std::vector <T>&> (components[component_id]);

    EntityV entity_v = get_entity_version(entity);

    Entity other = dense[size];
    EntityID other_id = get_entity_id(other);
    EntityV other_v = get_entity_version(other);
    auto other_ind = sparse[other_id];

    {
        std::swap(dense[entity_ind], dense[other_ind]);

        sparse[entity_id] = NULLADDR;
        sparse[other_id] = entity_ind;
    }

    {
        if (ondestroy_callbacks.size() > component_id) {
            auto& callback_any = ondestroy_callbacks[component_id];

            if (callback_any.has_value()) {
                auto& callback = std::any_cast <std::function <void(T&)>&> (callback_any);

                callback(component_arr[entity_ind]);
            } 
        }

        component_arr[entity_ind] = component_arr[other_ind];
    }
}

template <class T>
auto fun::ecs::get_entity(const T* component_ptr) -> Entity {
    const ComponentID component_id = get_component_id <T> ();

    return denses[component_id][component_ptr - &std::any_cast <std::vector <T>&> (components[component_id])[0]];
}

template <class T>
auto fun::ecs::oncreate_callback(std::function <void(T&)>&& f) -> void {
    const ComponentID component_id = get_component_id <T> ();

    if (oncreate_callbacks.size() <= component_id) {
        oncreate_callbacks.resize(component_id + 1);
    }

    oncreate_callbacks[component_id] = f;
}

template <class T>
auto fun::ecs::ondestroy_callback(std::function <void(T&)>&& f) -> void {
    const ComponentID component_id = get_component_id <T> ();

    if (ondestroy_callbacks.size() <= component_id) {
        ondestroy_callbacks.resize(component_id + 1);
    }

    ondestroy_callbacks[component_id] = f;
}