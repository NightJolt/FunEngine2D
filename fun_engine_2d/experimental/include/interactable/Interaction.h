#pragma once

#include "../../../core/include/globals.h"

#include "../../../core/include/render/WindowManager.h"

#include "Interactable.h"

namespace fun {
    class Interactable;

    class Interaction {
    public:

        static void Add(Interactable*);

        static void Update();

    private:

        static void Dispose(Interactable*);

        static Interactable* obj_active;
        static Interactable* obj_last;

        static std::vector <Interactable*> interactables;
    };
}
