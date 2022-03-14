#include "interactable/Interaction.h"

static fun::Interactable* obj_active;
static fun::Interactable* obj_last;

void fun::interaction::update() {
    vec2f_t mouse_pos = wndmgr::main_window->GetMouseWorldPosition();

    if (obj_last) {
        obj_last->m_r_released = false;
        obj_last->m_l_released = false;
        obj_last->m_hover_exit = false;

        obj_last = nullptr;
    }

    if (obj_active) {
        bool interaction = obj_active->m_interaction_fun(mouse_pos);
        bool is_interacted = interaction || obj_active->m_l_pressed || obj_active->m_l_hold || obj_active->m_l_released || obj_active->m_r_pressed || obj_active->m_r_hold || obj_active->m_r_released;

        if (is_interacted) {
            obj_active->m_l_pressed = false;
            obj_active->m_l_released = false;

            if (interaction) {
                if (input::pressed(sf::Mouse::Left)) {
                    if (!obj_active->m_l_hold) {
                        obj_active->m_l_pressed = true;
                        obj_active->m_l_hold = true;
                    }
                }
            }

            if (input::released(sf::Mouse::Left)) {
                if (obj_active->m_l_hold) {
                    obj_active->m_l_hold = false;
                    obj_active->m_l_released = true;
                }
            }

            obj_active->m_r_pressed = false;
            obj_active->m_r_released = false;

            if (interaction) {
                if (input::pressed(sf::Mouse::Right)) {
                    if (!obj_active->m_r_hold) {
                        obj_active->m_r_pressed = true;
                        obj_active->m_r_hold = true;
                    }
                }
            }

            if (input::released(sf::Mouse::Right)) {
                if (obj_active->m_r_hold) {
                    obj_active->m_r_hold = false;
                    obj_active->m_r_released = true;
                }
            }

            if (obj_active->m_hover_enter) {
                obj_active->m_hover_enter = false;
                obj_active->m_hovered = true;
            }
        } else {
            if (obj_active->m_l_pressed || obj_active->m_l_hold) {
                obj_active->m_l_pressed = false;
                obj_active->m_l_hold = false;
                obj_active->m_l_released = true;
            }

            if (obj_active->m_r_pressed || obj_active->m_r_hold) {
                obj_active->m_r_pressed = false;
                obj_active->m_r_hold = false;
                obj_active->m_r_released = true;
            }

            obj_active->m_hover_enter = false;
            obj_active->m_hovered = false;
            obj_active->m_hover_exit = true;

            obj_last = obj_active;
            obj_active = nullptr;
        }
    }

    if (obj_active) {
        if (!(obj_active->m_l_hold || obj_active->m_r_hold)) {
            Interactable* new_target = object_at_pos(mouse_pos.to_sf());

            if (!new_target) new_target = obj_active;

            if (new_target != obj_active) {
                obj_active->m_hover_exit = true;
                new_target->m_hover_enter = true;

                obj_last = obj_active;
                obj_active = new_target;
            }
        }
    } else {
        obj_active = object_at_pos(mouse_pos.to_sf());

        if (!obj_active) return;

        obj_active->m_hover_enter = true;
    }
}

fun::Interactable* fun::interaction::object_at_pos(sf::Vector2f pos) {
    Interactable* target = nullptr;

    for (auto& interactable : ecs::iterate_component <Interactable> ()) {
        if (interactable.m_interaction_fun(pos)) {
            if (!target || target->m_layer < interactable.m_layer) {
                target = &interactable;
            }
        }
    }

    return target;
}

bool fun::interaction::is_anything_interacted() {
    return obj_active;
}