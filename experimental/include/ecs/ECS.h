#pragma once

#include "../../../core/include/globals.h"

namespace fun::ecs {
    typedef uint64_t Entity;
    typedef uint32_t EntityID;
    typedef uint32_t EntityV;

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

    class Component {
    public:

        virtual void Update() = 0;
    };
}