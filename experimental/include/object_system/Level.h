#pragma once

#include "../../../core/include/globals.h"

#include "StaticObject.h"
#include "LiveObject.h"

namespace fun {
    class Level final {
    public:

        explicit Level(const std::string& = "unnamed");
        ~Level() = default;

        template <class T>
        T* CreateStaticObject(const std::string name = "unnamed") {
            T* object = new T;

            live_objects.emplace_back(dynamic_cast <StaticObject*> (object))->Init();
            
            object->name = name;

            return object;
        }

        template <class T>
        T* CreateLiveObject(const std::string name = "unnamed") {
            T* object = new T;

            live_objects.emplace_back(dynamic_cast <LiveObject*> (object))->Init();

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
            std::vector <Object*> objects;

            for (auto object : static_objects) {
                if (dynamic_cast <T*> (object)) {
                    objects.template emplace_back(object);
                }
            }

            for (auto object : live_objects) {
                if (dynamic_cast <T*> (object)) {
                    objects.template emplace_back(object);
                }
            }

            return objects;
        }

        std::string name;

    private:

        std::vector <StaticObject*> static_objects;
        std::vector <LiveObject*> live_objects;
    };
}