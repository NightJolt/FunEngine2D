#pragma once

#include "../../../core/include/globals.h"

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

    template <class T, class... Args>
    void add_component(Entity, Args&&...);

    template <class T>
    void remove_component(Entity);

    template <class T>
    Entity get_entity(T*);

    template <class T>
    void oncreate_callback(const std::function <void(T&)>&);

    template <class T>
    void ondestroy_callback(const std::function <void(T&)>&);


    // void show_hierarchy();
    // void show_components();
}

#include "ECS.tpp"