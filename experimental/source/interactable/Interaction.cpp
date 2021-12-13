#include "interactable/Interaction.h"

fun::Interactable* fun::Interaction::obj_active = nullptr;
fun::Interactable* fun::Interaction::obj_last = nullptr;

std::vector <fun::Interactable*> fun::Interaction::interactables = std::vector <fun::Interactable*> ();

void fun::Interaction::Add(fun::Interactable* interactable) {
    interactables.emplace_back(interactable);
}

void fun::Interaction::Update() {
    sf::Vector2 mouse_pos = WindowManager::main_window->GetMouseWorldPosition();

    if (obj_last) {
        obj_last->r_released = false;
        obj_last->l_released = false;
        obj_last->hover_exit = false;

        obj_last = nullptr;
    }

    if (obj_active) {
        bool interaction = obj_active->Interactable_Interaction(mouse_pos);
        bool is_interacted = interaction || obj_active->l_pressed || obj_active->l_hold || obj_active->l_released || obj_active->r_pressed || obj_active->r_hold || obj_active->r_released;

        if (is_interacted) {
            obj_active->l_pressed = false;
            obj_active->l_released = false;

            if (interaction) {
                if (input::pressed(sf::Mouse::Left)) {
                    if (!obj_active->l_hold) {
                        obj_active->l_pressed = true;
                        obj_active->l_hold = true;
                    }
                }
            }

            if (input::released(sf::Mouse::Left)) {
                if (obj_active->l_hold) {
                    obj_active->l_hold = false;
                    obj_active->l_released = true;
                }
            }

            obj_active->r_pressed = false;
            obj_active->r_released = false;

            if (interaction) {
                if (input::pressed(sf::Mouse::Right)) {
                    if (!obj_active->r_hold) {
                        obj_active->r_pressed = true;
                        obj_active->r_hold = true;
                    }
                }
            }

            if (input::released(sf::Mouse::Right)) {
                if (obj_active->r_hold) {
                    obj_active->r_hold = false;
                    obj_active->r_released = true;
                }
            }

            if (obj_active->hover_enter) {
                obj_active->hover_enter = false;
                obj_active->hovered = true;
            }
        } else {
            if (obj_active->l_pressed || obj_active->l_hold) {
                obj_active->l_pressed = false;
                obj_active->l_hold = false;
                obj_active->l_released = true;
            }

            if (obj_active->r_pressed || obj_active->r_hold) {
                obj_active->r_pressed = false;
                obj_active->r_hold = false;
                obj_active->r_released = true;
            }

            obj_active->hover_enter = false;
            obj_active->hovered = false;
            obj_active->hover_exit = true;

            obj_last = obj_active;
            obj_active = nullptr;
        }
    }

    if (obj_active) {
        if (!(obj_active->l_hold || obj_active->r_hold)) {
            Interactable* new_target = ObjectAtPos(mouse_pos);

            if (!new_target) new_target = obj_active;

            if (new_target != obj_active) {
                obj_active->hover_exit = true;
                new_target->hover_enter = true;

                obj_last = obj_active;
                obj_active = new_target;
            }
        }
    } else {
        obj_active = ObjectAtPos(mouse_pos);

        if (!obj_active) return;

        obj_active->hover_enter = true;
    }
}

void fun::Interaction::Dispose(Interactable* interactable) {
    for (auto it = interactables.rbegin(); it != interactables.rend(); it++) {
        if (*it == interactable) interactables.erase((it + 1).base());
    }
}

fun::Interactable* fun::Interaction::ObjectAtPos(const sf::Vector2f& pos) {
    Interactable* target = nullptr;

    for (auto object : interactables) {
        if (object->Interactable_Interaction(pos)) {
            if (!target || target->layer < object->layer) {
                target = object;
            }
        }
    }

    return target;
}

bool fun::Interaction::IsAnythingInteracted() {
    return obj_active;
}