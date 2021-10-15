#include "interactable/Interactable.h"

fun::Interactable::Interactable(i32 layer) : layer(layer) {
    Interaction::Add(this);

    r_pressed = false;
    r_hold = false;
    r_released = false;

    l_pressed = false;
    l_hold = false;
    l_released = false;

    hover_enter = false;
    hovered = false;
    hover_exit = false;
}

fun::Interactable::~Interactable() noexcept = default;

bool fun::Interactable::Interactable_RightPressed() const {
    return r_pressed;
}

bool fun::Interactable::Interactable_RightHold() const {
    return r_hold;
}

bool fun::Interactable::Interactable_RightReleased() const {
    return r_released;
}

bool fun::Interactable::Interactable_LeftPressed() const {
    return l_pressed;
}

bool fun::Interactable::Interactable_LeftHold() const {
    return l_hold;
}

bool fun::Interactable::Interactable_LeftReleased() const {
    return l_released;
}

bool fun::Interactable::Interactable_HoverEnter() const {
    return hover_enter;
}

bool fun::Interactable::Interactable_Hovered() const {
    return hovered;
}

bool fun::Interactable::Interactable_HoverExit() const {
    return hover_exit;
}

void fun::Interactable::Interactable_SetInteractionLayer(i32 new_layer) {
    layer = new_layer;
}

i32 fun::Interactable::Interactable_GetInteractionLayer() const {
    return layer;
}