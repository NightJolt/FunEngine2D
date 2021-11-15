#pragma once

#include "../../../core/include/globals.h"

#include "../../../core/include/Math.h"
#include "../../../core/include/Input.h"

#include "../object_system/LiveObject.h"
#include "Interaction.h"

namespace fun {
    class Interaction;

    class Interactable {
        friend Interaction;

    public:

        Interactable();
        virtual ~Interactable() noexcept = 0;

        void Interactable_SetInteractionLayer(i32);
        i32 Interactable_GetInteractionLayer() const;

        [[nodiscard]] bool Interactable_RightPressed() const;
        [[nodiscard]] bool Interactable_RightHold() const;
        [[nodiscard]] bool Interactable_RightReleased() const;

        [[nodiscard]] bool Interactable_LeftPressed() const;
        [[nodiscard]] bool Interactable_LeftHold() const;
        [[nodiscard]] bool Interactable_LeftReleased() const;

        [[nodiscard]] bool Interactable_HoverEnter() const;
        [[nodiscard]] bool Interactable_Hovered() const;
        [[nodiscard]] bool Interactable_HoverExit() const;

        virtual bool Interactable_Interaction(const sf::Vector2f&) = 0;

    private:

        bool r_pressed;
        bool r_hold;
        bool r_released;

        bool l_pressed;
        bool l_hold;
        bool l_released;

        bool hover_enter;
        bool hovered;
        bool hover_exit;

        i32 layer;
    };
}