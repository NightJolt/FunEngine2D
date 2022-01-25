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

    // get_entities <T, ...>

    template <class T>
    struct ComponentIterator {
        ComponentIterator(std::vector <uint8_t>* array) {
            component_size = sizeof(T);

            current = &*array->begin();

            if (array->empty()) {
                end = current;
            } else {
                end = &*(array->end() - 1) + 1;
            }
        }

        bool empty() {
            return current == end;
        }

        T& get() {
            return *reinterpret_cast <T*> (current);
        }

        void next() {
            current += component_size;
        }

        size_t component_size;
        uint8_t* current;
        uint8_t* end;
    };

    std::vector <uint8_t>* get_components_array(ComponentID component_id);
    std::vector <Entity>*  get_entities_array(ComponentID component_id);

    template <class T>
    ComponentIterator <T> iterate_components() {
        return ComponentIterator <T> (get_components_array(get_component_id <T> ()));
    }

    // todo: support multiple components
    template <class T>
    std::vector <Entity>& get_entities() {
        return *get_entities_array(get_component_id <T> ());
    }

    bool has_component(Entity entity, ComponentID component_id);
    void add_component(Entity entity, ComponentID component_id, size_t component_size, std::function <void(uint8_t*)>);
    uint8_t* get_component(Entity entity, ComponentID component_id, size_t component_size);
    void remove_component(Entity entity, ComponentID component_id, size_t component_size);

    template <class T>
    bool has_component(Entity entity) {
        return has_component(entity, get_component_id <T> ());
    }

    template <class T>
    void add_component(Entity entity) {
        add_component(entity, get_component_id <T> (), sizeof(T), [](uint8_t* ptr) -> void { *reinterpret_cast <T*> (ptr) = T(); });
    }

    template <class T>
    T& get_component(Entity entity) {
        return *reinterpret_cast <T*> (get_component(entity, get_component_id <T> (), sizeof(T)));
    }

    template <class T>
    void remove_component(Entity entity) {
        remove_component(entity, get_component_id <T> (), sizeof(T));
    }

    void show_components();
}