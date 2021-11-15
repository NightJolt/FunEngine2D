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
        static void Dispose(Interactable*);

        static Interactable* ObjectAtPos(const sf::Vector2f&);

    private:

        static Interactable* obj_active;
        static Interactable* obj_last;

        static std::vector <Interactable*> interactables;
    };
}
