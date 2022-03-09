#pragma once

#include "../Globals.h"

namespace fun::ecs {
    typedef uint64_t Entity;
    typedef uint32_t EntityID;
    typedef uint32_t EntityV;
    typedef uint8_t ComponentID;

    typedef std::vector <Entity> dense_t;
    typedef std::vector <size_t> sparse_t;

    constexpr uint64_t NULLENTITY = ~(uint64_t)0;
    constexpr size_t NULLADDR = ~(size_t)0;
    
    extern std::vector <Entity> entities;

    extern EntityID available;
    extern Entity next;

    extern std::vector <dense_t> denses;
    extern std::vector <sparse_t> sparses;
    extern std::vector <std::any> components;
    extern std::vector <size_t> sizes;

    extern std::vector <std::any> oncreate_callbacks;
    extern std::vector <std::any> ondestroy_callbacks;

    extern ComponentID next_component_id;


    EntityID get_entity_id(Entity);
    EntityV get_entity_version(Entity);

    Entity generate_entity_uuid(EntityID, EntityV);
    Entity create_entity();
    Entity recycle_entity();
    void destroy_entity(Entity);
    bool is_entity_recyclable(Entity);

    bool is_entity_alive(Entity);
    bool is_id_alive(EntityID);
    Entity new_entity();


    template <class T>
    ComponentID get_component_id();

    // todo: support multiple components
    // ! Needs iterator
    // template <class T>
    // std::vector <Entity>& get_entities();

    template <class T>
    struct ComponentIterator {
        T* begin_p;
        T* end_p;
        T* ptr;

        ComponentIterator() : begin_p(nullptr), end_p(nullptr) {}
        ComponentIterator(std::vector <T>& v, size_t n) : begin_p(n ? &v[0] : nullptr), end_p(n ? &v[n - 1] + 1 : nullptr), ptr(begin_p) {}

        T* begin() { return begin_p; }
        const T* begin() const { return begin_p; }
        T* end() { return end_p; }
        const T* end() const { return end_p; }

        // T& operator *() { return *ptr; }
        // T* operator ->() { return ptr; }
        // void operator ++() { ++ptr; }
        // bool operator !=(T* t) { return ptr != t; }

    };

    template <class T>
    bool component_exist();

    template <class T>
    ComponentIterator <T> iterate_component();

    template <class T>
    std::vector <T>& get_component_array();

    template <class T>
    T& get_component(Entity);

    template <class T>
    bool has_component(Entity);
    bool has_component(Entity, ComponentID);

    template <class T, class... Args>
    void add_component(Entity, Args&&...);

    template <class T>
    void remove_component(Entity);
    void remove_component(Entity, ComponentID);

    template <class T>
    Entity get_entity(T&);

    template <class T>
    void oncreate_callback(const std::function <void(T&)>&);

    template <class T>
    void ondestroy_callback(const std::function <void(T&)>&);


    // void show_hierarchy();
    // void show_components();
}










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
auto fun::ecs::component_exist() -> bool {
    const ComponentID component_id = get_component_id <T> ();

    return components.size() > component_id && components[component_id].has_value();
}

template <class T>
auto fun::ecs::iterate_component() -> ComponentIterator <T> {
    const ComponentID component_id = get_component_id <T> ();

    if (component_exist <T> ())
        return ComponentIterator <T> (std::any_cast <std::vector <T>&> (components[component_id]), sizes[component_id]);
    else
        return ComponentIterator <T> ();
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
    EntityV entity_v = get_entity_version(entity);

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

    if (entity_ind == size) goto skip_index_swap;

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

    skip_index_swap:

    {
        if (ondestroy_callbacks.size() > component_id) {
            auto& callback_any = ondestroy_callbacks[component_id];

            if (callback_any.has_value()) {
                auto& callback = std::any_cast <std::function <void(T&)>&> (callback_any);

                callback(component_arr[entity_ind]);
            } 
        }

        component_arr[entity_ind] = std::move(component_arr[other_ind]);
    }
}

template <class T>
auto fun::ecs::get_entity(T& component) -> Entity {
    const ComponentID component_id = get_component_id <T> ();

    return denses[component_id][&component - &std::any_cast <std::vector <T>&> (components[component_id])[0]];
}

template <class T>
auto fun::ecs::oncreate_callback(const std::function <void(T&)>& f) -> void {
    const ComponentID component_id = get_component_id <T> ();

    if (oncreate_callbacks.size() <= component_id) {
        oncreate_callbacks.resize(component_id + 1);
    }

    oncreate_callbacks[component_id] = std::move(f);
}

template <class T>
auto fun::ecs::ondestroy_callback(const std::function <void(T&)>& f) -> void {
    const ComponentID component_id = get_component_id <T> ();

    if (ondestroy_callbacks.size() <= component_id) {
        ondestroy_callbacks.resize(component_id + 1);
    }

    ondestroy_callbacks[component_id] = std::move(f);
}