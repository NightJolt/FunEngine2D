#pragma once

#include "../../../core/include/globals.h"

#include "StaticObject.h"
#include "LiveObject.h"

namespace fun {
    class Level {
    public:

        Level();
        ~Level() = default;

        template <class T>
        T& CreateStaticObject() { return static_objects.emplace_back(new T); }

        template <class T>
        T& CreateLiveObject() { return live_objects.emplace_back(new T); }

        void Init();
        void Update();
        void Dispose();

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

    private:

        std::vector <StaticObject*> static_objects;
        std::vector <LiveObject*> live_objects;
    };
}