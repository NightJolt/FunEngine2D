#include "interact/interaction.h"

static fun::ecs::entity_t entity_active = fun::ecs::nullentity;
static fun::ecs::entity_t entity_last = fun::ecs::nullentity;

void fun::interaction::update() {
    vec2f_t mouse_pos = winmgr::main_window->get_mouse_world_position();

    entity_active = ecs::validate_entity(entity_active);
    entity_last = ecs::validate_entity(entity_last);

    if (entity_last != fun::ecs::nullentity) {
        auto& interactable = ecs::get_component <interactable_t> (entity_last);

        interactable.right_released = false;
        interactable.left_released = false;
        interactable.hover_exit = false;

        entity_last = ecs::nullentity;
    }

    if (entity_active != fun::ecs::nullentity) {
        auto& interactable = ecs::get_component <interactable_t> (entity_active);

        bool is_mouse_interacted = interactable.interaction_fun(mouse_pos);
        bool is_left_interacted = interactable.left_pressed || interactable.left_hold || interactable.left_released;
        bool is_right_interacted = interactable.right_pressed || interactable.right_hold || interactable.right_released;
        bool is_interacted = is_mouse_interacted || is_left_interacted || is_right_interacted;

        if (is_interacted) {
            interactable.left_pressed = false;
            interactable.left_released = false;

            if (is_mouse_interacted) {
                if (input::pressed(sf::Mouse::Left)) {
                    if (interactable.left_hold) {
                        interactable.left_pressed = true;
                        interactable.left_hold = true;
                    }
                }
            }

            if (input::released(sf::Mouse::Left)) {
                if (interactable.left_hold) {
                    interactable.left_hold = false;
                    interactable.left_released = true;
                }
            }

            interactable.right_pressed = false;
            interactable.right_released = false;

            if (is_mouse_interacted) {
                if (input::pressed(sf::Mouse::Right)) {
                    if (interactable.right_hold) {
                        interactable.right_pressed = true;
                        interactable.right_hold = true;
                    }
                }
            }

            if (input::released(sf::Mouse::Right)) {
                if (interactable.right_hold) {
                    interactable.right_hold = false;
                    interactable.right_released = true;
                }
            }

            if (interactable.hover_enter) {
                interactable.hover_enter = false;
                interactable.hover_hold = true;
            }
        } else {
            if (interactable.left_pressed || interactable.left_hold) {
                interactable.left_pressed = false;
                interactable.left_hold = false;
                interactable.left_released = true;
            }

            if (interactable.right_pressed || interactable.right_hold) {
                interactable.right_pressed = false;
                interactable.right_hold = false;
                interactable.right_released = true;
            }

            interactable.hover_enter = false;
            interactable.hover_hold = false;
            interactable.hover_exit = true;

            entity_last = entity_active;
            entity_active = ecs::nullentity;
        }
    }

    if (entity_active != fun::ecs::nullentity) {
        auto& interactable = ecs::get_component <interactable_t> (entity_active);
        
        if (!interactable.left_hold && !interactable.right_hold) {
            ecs::entity_t new_entity = entity_at_pos(mouse_pos.to_sf());

            if (new_entity == ecs::nullentity) new_entity = entity_active;

            if (new_entity != entity_active) {
                interactable.hover_exit = true;
                ecs::get_component <interactable_t> (new_entity).hover_enter = true;

                entity_last = entity_active;
                entity_active = new_entity;
            }
        }
    } else {
        entity_active = entity_at_pos(mouse_pos.to_sf());

        if (entity_active != ecs::nullentity) {
            ecs::get_component <interactable_t> (entity_active).hover_enter = true;
        }
    }
}

fun::ecs::entity_t fun::interaction::entity_at_pos(vec2f_t pos) {
    fun::ecs::entity_t target = ecs::nullentity;
    layer_t target_layer = 0;

    for (auto& interactable : ecs::iterate_component <interactable_t> ()) {
        if (interactable.interaction_fun(pos)) {
            layer_t current_layer = interactable.layer;

            if (target == ecs::nullentity || target_layer < current_layer) {
                target = ecs::get_entity(interactable);
                target_layer = current_layer;
            }
        }
    }

    return target;
}

bool fun::interaction::is_anything_interacted() {
    return ecs::validate_entity(entity_active) != ecs::nullentity;
}
