#pragma once

#include "../../../core/include/globals.h"
#include "../../../core/include/tools/Debugger.h"

namespace fun::ecs {
    typedef uint64_t Entity;
    typedef uint32_t EntityID;
    typedef uint32_t EntityV;

    #define NULLENTITY -1

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

    void show_hierarchy();

    // void allocate(int);
    // void reserve(int);

    typedef uint8_t ComponentID;

    extern ComponentID next_component_id;
    template <class T>
    ComponentID get_component_id() {
        static ComponentID id = next_component_id++;

        return id;
    }

    bool add_component(Entity entity, ComponentID component_id, size_t component_size, std::function <void(uint8_t*)>);
    bool has_component(Entity entity, ComponentID component_id);
    bool remove_component(Entity entity, ComponentID component_id, size_t component_size);

    template <class T>
    bool add_component(Entity entity) {
        return add_component(entity, get_component_id <T> (), sizeof(T), [](uint8_t* ptr) -> void { *reinterpret_cast <T*> (ptr) = T(); });
    }

    // template <class T>
    // T* get_component(Entity entity) {
    //     return new T;
    // }

    template <class T>
    bool has_component(Entity entity) {
        return has_component(entity, get_component_id <T> ());
    }

    template <class T>
    bool remove_component(Entity entity) {
        return remove_component(entity, get_component_id <T> (), sizeof(T));
    }

    void show_components();
}