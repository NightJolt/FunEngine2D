#pragma once

#include "../../../core/include/globals.h"

namespace fun::ecs {
    typedef uint64_t Entity;
    typedef uint32_t EntityID;
    typedef uint32_t EntityV;
    typedef uint8_t ComponentID;

    typedef std::vector <Entity> dense_t;
    typedef std::vector <size_t> sparse_t;

    constexpr int NULLENTITY = -1;
    constexpr int NULLADDR = -1;
    
    extern std::vector <Entity> entities;

    extern EntityID available;
    extern Entity next;

    extern std::vector <dense_t> denses;
    extern std::vector <sparse_t> sparses;
    extern std::vector <std::any> components;
    extern std::vector <size_t> sizes;

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
    template <class T>
    std::vector <Entity>& get_entities();

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


    // void show_hierarchy();
    // void show_components();
}

#include "ECS.tpp"