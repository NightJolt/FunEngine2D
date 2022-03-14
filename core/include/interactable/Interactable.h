#pragma once

#include "../Globals.h"
#include "../_Math.h"
#include "../Input.h"

namespace fun {
    struct Interactable {
        typedef int32_t layer_t;

        explicit Interactable(const std::function <bool(vec2f_t)>&, layer_t = 0);

        void SetInteractionLayer(uint32_t);
        uint32_t GetInteractionLayer() const;

        [[nodiscard]] bool RightPressed() const;
        [[nodiscard]] bool RightHold() const;
        [[nodiscard]] bool RightReleased() const;

        [[nodiscard]] bool LeftPressed() const;
        [[nodiscard]] bool LeftHold() const;
        [[nodiscard]] bool LeftReleased() const;

        [[nodiscard]] bool HoverEnter() const;
        [[nodiscard]] bool Hovered() const;
        [[nodiscard]] bool HoverExit() const;


        bool m_r_pressed;
        bool m_r_hold;
        bool m_r_released;

        bool m_l_pressed;
        bool m_l_hold;
        bool m_l_released;

        bool m_hover_enter;
        bool m_hovered;
        bool m_hover_exit;

        layer_t m_layer;

        std::function <bool(vec2f_t)> m_interaction_fun;
    };
}