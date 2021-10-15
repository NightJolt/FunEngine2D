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
        bool is_interacted = interaction || obj_active->l_hold || obj_active->r_pressed || obj_active->r_hold;

        if (is_interacted) {
            obj_active->l_pressed = false;
            obj_active->l_released = false;

            if (interaction) {
                if (Input::Pressed(sf::Mouse::Left)) {
                    if (!obj_active->l_hold) {
                        obj_active->l_pressed = true;
                        obj_active->l_hold = true;
                    }
                } else if (Input::Released(sf::Mouse::Left)) {
                    if (obj_active->l_hold) {
                        obj_active->l_hold = false;
                        obj_active->l_released = true;
                    }
                }
            }

            obj_active->r_pressed = false;
            obj_active->r_released = false;

            if (interaction) {
                if (Input::Pressed(sf::Mouse::Right)) {
                    if (!obj_active->r_hold) {
                        obj_active->r_pressed = true;
                        obj_active->r_hold = true;
                    }
                } else if (Input::Released(sf::Mouse::Right)) {
                    if (obj_active->r_hold) {
                        obj_active->r_hold = false;
                        obj_active->r_released = true;
                    }
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

    if (!obj_active) {
        for (auto object : interactables) {
            if (object->Interactable_Interaction(mouse_pos)) {
                if (!obj_active || obj_active->layer < object->layer) {
                    obj_active = object;
                }
            }
        }

        if (!obj_active) return;

        obj_active->hover_enter = true;
    }
}

void fun::Interaction::Dispose(fun::Interactable *) {
    // todo: implement
}