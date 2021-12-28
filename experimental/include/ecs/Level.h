#pragma once

#include "../../../core/include/globals.h"

#include "Entity.h"

namespace fun {
    class Level final {
    public:

        explicit Level(const std::string& = "unnamed");
        ~Level() = default;

        template <class T>
        T* CreateEntity(const std::string name = "unnamed") {
            T* object = new T;

            entities.emplace_back(dynamic_cast <Entity*> (object))->Init();
            
            object->name = name;

            return object;
        }

        void Init();
        void Update();
        void Dispose();
        void Unload();

        void ShowHierarchy();

        template <class T>
        std::vector <T*> GetObjectsOfType() {
            // std::vector <Entity*> entities_of_type;

            // for (auto entity : entities) {
            //     if (dynamic_cast <T*> (entity)) {
            //         objects.emplace_back(entity);
            //     }
            // }

            return vector <T*> ();
        }

        std::string name;

    private:

        std::vector <Entity*> entities;
    };
}