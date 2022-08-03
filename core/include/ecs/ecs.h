#pragma once

#include "../globals.h"

namespace fun::ecs {
    typedef uint64_t entity_t;
    typedef uint32_t entity_id_t;
    typedef uint32_t entity_ver_t;
    typedef uint8_t component_id_t;
    typedef uint32_t addr_t;

    typedef std::vector <entity_t> dense_t;
    typedef std::vector <addr_t> sparse_t;

    constexpr entity_t nullentity = ~(entity_t)0;
    constexpr addr_t nulladdr = ~(addr_t)0;
    
    extern std::vector <fun::ecs::entity_t> entities;

    extern entity_id_t available;
    extern entity_t next;

    extern std::vector <dense_t> denses;
    extern std::vector <sparse_t> sparses;
    extern std::vector <std::any> components;
    extern std::vector <uint32_t> sizes;

    extern std::vector <std::any> oncreate_callbacks;
    extern std::vector <std::any> ondestroy_callbacks;

    extern component_id_t next_component_id;


    entity_id_t get_entity_id(entity_t);
    entity_ver_t get_entity_version(entity_t);

    entity_t generate_entity_uuid(entity_id_t, entity_ver_t);
    entity_t create_entity();
    entity_t recycle_entity();
    void destroy_entity(entity_t);
    bool is_entity_recyclable(entity_t);

    bool is_entity_alive(entity_t);
    bool is_id_alive(entity_id_t);
    entity_t new_entity();

    entity_t validate_entity(entity_t);


    template <class T>
    component_id_t get_component_id();

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
    T& get_component(entity_t);

    template <class T>
    bool has_component(entity_t);
    bool has_component(entity_t, component_id_t);

    template <class T, class... Args>
    T& add_component(entity_t, Args&&...);

    template <class T>
    void remove_component(entity_t);
    void remove_component(entity_t, component_id_t);

    template <class T>
    entity_t get_entity(T&);

    template <class T>
    void oncreate_callback(const std::function <void(T&)>&);

    template <class T>
    void ondestroy_callback(const std::function <void(T&)>&);


    // void show_hierarchy();
    // void show_components();
}










template <class T>
auto fun::ecs::get_component_id() -> component_id_t {
    static component_id_t id = next_component_id++;

    return id;
}

// template <class T>
// auto fun::ecs::get_entities() -> std::vector <Entity>& {
//     return denses[get_component_id <T> ()];
// }

template <class T>
auto fun::ecs::component_exist() -> bool {
    const component_id_t component_id = get_component_id <T> ();

    return components.size() > component_id && components[component_id].has_value();
}

template <class T>
auto fun::ecs::iterate_component() -> ComponentIterator <T> {
    const component_id_t component_id = get_component_id <T> ();

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
auto fun::ecs::get_component(entity_t entity) -> T& {
    return get_component_array <T> ()[sparses[get_component_id <T> ()][get_entity_id(entity)]];
}

template <class T>
auto fun::ecs::has_component(entity_t entity) -> bool {
    const component_id_t component_id = get_component_id <T> ();

    if (!is_entity_alive(entity) || sizes.size() <= component_id) return false;

    entity_id_t entity_id = get_entity_id(entity);
    entity_ver_t entity_v = get_entity_version(entity);

    auto& dense = denses[component_id];
    auto& sparse = sparses[component_id];
    
    if (sparse.size() <= entity_id) return false;

    auto dense_index = sparse[entity_id];

    if (sizes[component_id] <= dense_index) return false;

    return get_entity_version(dense[dense_index]) == entity_v;
}

template <class T, class... Args>
auto fun::ecs::add_component(entity_t entity, Args&&... args) -> T& {
    const component_id_t component_id = get_component_id <T> ();

    if (sizes.size() <= component_id) {
        auto new_size = component_id + 1;

        denses.resize(new_size, dense_t());
        sparses.resize(new_size, sparse_t());
        components.resize(new_size);
        sizes.resize(new_size, 0);
    }

    entity_id_t entity_id = get_entity_id(entity);
    entity_ver_t entity_v = get_entity_version(entity);

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
            sparse.resize(entity_id + 1, nulladdr);
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

    return component_arr[size];
}

template <class T>
auto fun::ecs::remove_component(entity_t entity) -> void {
    const component_id_t component_id = get_component_id <T> ();
    
    auto size = --sizes[component_id];
    
    entity_id_t entity_id = get_entity_id(entity);
    auto& sparse = sparses[component_id];
    auto entity_ind = sparse[entity_id];

    auto& dense = denses[component_id];
    auto& component_arr = std::any_cast <std::vector <T>&> (components[component_id]);

    entity_ver_t entity_v = get_entity_version(entity);

    entity_t other = dense[size];
    entity_id_t other_id = get_entity_id(other);
    entity_ver_t other_v = get_entity_version(other);
    addr_t other_ind = sparse[other_id];

    if (entity_ind != size) {
        std::swap(dense[entity_ind], dense[other_ind]);

        sparse[entity_id] = nulladdr;
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

        component_arr[entity_ind] = std::move(component_arr[other_ind]);
    }
}

template <class T>
auto fun::ecs::get_entity(T& component) -> entity_t {
    const component_id_t component_id = get_component_id <T> ();

    return denses[component_id][&component - &std::any_cast <std::vector <T>&> (components[component_id])[0]];
}

template <class T>
auto fun::ecs::oncreate_callback(const std::function <void(T&)>& f) -> void {
    const component_id_t component_id = get_component_id <T> ();

    if (oncreate_callbacks.size() <= component_id) {
        oncreate_callbacks.resize(component_id + 1);
    }

    oncreate_callbacks[component_id] = std::move(f);
}

template <class T>
auto fun::ecs::ondestroy_callback(const std::function <void(T&)>& f) -> void {
    const component_id_t component_id = get_component_id <T> ();

    if (ondestroy_callbacks.size() <= component_id) {
        ondestroy_callbacks.resize(component_id + 1);
    }

    ondestroy_callbacks[component_id] = std::move(f);
}
