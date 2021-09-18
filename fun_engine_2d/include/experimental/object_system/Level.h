#pragma once

#include "../../core/globals.h"

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

    private:

        std::vector <StaticObject*> static_objects;
        std::vector <LiveObject*> live_objects;
    };
}