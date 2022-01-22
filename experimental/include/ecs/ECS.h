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

    void allocate(int);
    void reserve(int);

    typedef uint8_t ComponentID;

    template <class T>
    bool get_component_id() {
        static ComponentID id = 0;

        return ++id;
    }

    extern std::vector <std::vector <EntityV>> denses;
    extern std::vector <std::vector <EntityID>> sparses;
    extern std::vector <std::vector <uint8_t>> components;
    extern std::vector <uint32_t> sizes;

    template <class T>
    void add_component(Entity entity) {
        if (!is_entity_alive(entity) || has_component <T> (entity)) return;

        ComponentID component_id = get_component_id <T> ();
        EntityID entity_id = get_entity_id(entity);
        EntityID entity_v = get_entity_version(entity);

        auto* dense = &denses[component_id];
        auto* sparse = &sparses[component_id];
        auto* t_componets = &components[component_id];
        auto* size_p = &sizes[component_id];
        auto size = *size_p;

        {
            if (dense->size() > size) {
                dense->emplace_back(entity_v);
            } else {
                (*dense)[size] = entity_v;
            }

            *size_p++;
        }

        {
            if (sparse->size() <= entity_id) {
                sparse->resize(entity_id + 1);
            }

            (*sparse)[entity_id] = size;
        }

        {
            uint64_t length = (static_cast <uint64_t> (size) + 1) * sizeof(T);
            uint64_t arr_length = t_componets->size();

            if (arr_length <= length) {
                t_componets->resize(arr_length + sizeof(T));
            }

            *reinterpret_cast <T*> (t_componets + length - 1) = T();
        }
    }

    template <class T>
    bool has_component(Entity entity) {
        return false;
    }

    template <class T>
    bool remove_component(Entity entity) {} 

    class Component {
    public:

        virtual void Update() = 0;
    };
}