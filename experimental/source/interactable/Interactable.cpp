#include "interactable/Interactable.h"

fun::Interactable::Interactable(const std::function <bool(sf::Vector2f)>& interaction_fun, layer_t layer) : m_interaction_fun(std::move(interaction_fun)), m_layer(layer) {
    m_r_pressed = false;
    m_r_hold = false;
    m_r_released = false;

    m_l_pressed = false;
    m_l_hold = false;
    m_l_released = false;

    m_hover_enter = false;
    m_hovered = false;
    m_hover_exit = false;
}

bool fun::Interactable::RightPressed() const {
    return m_r_pressed;
}

bool fun::Interactable::RightHold() const {
    return m_r_hold;
}

bool fun::Interactable::RightReleased() const {
    return m_r_released;
}

bool fun::Interactable::LeftPressed() const {
    return m_l_pressed;
}

bool fun::Interactable::LeftHold() const {
    return m_l_hold;
}

bool fun::Interactable::LeftReleased() const {
    return m_l_released;
}

bool fun::Interactable::HoverEnter() const {
    return m_hover_enter;
}

bool fun::Interactable::Hovered() const {
    return m_hovered;
}

bool fun::Interactable::HoverExit() const {
    return m_hover_exit;
}

void fun::Interactable::SetInteractionLayer(uint32_t layer) {
    m_layer = layer;
}

uint32_t fun::Interactable::GetInteractionLayer() const {
    return m_layer;
}