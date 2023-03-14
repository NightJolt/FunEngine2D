#include "interact/interactable.h"
#include "_math.h"
#include "input.h"

fun::interactable_t::interactable_t(const interact_fun_t& interaction_fun, const action_fun_t& action_fun, layer_t layer) :
right_pressed(false),
right_hold(false),
right_released(false),

left_pressed(false),
left_hold(false),
left_released(false),

hover_enter(false),
hover_hold(false),
hover_exit(false),

mouse_left_offset(),
mouse_right_offset(),
layer(layer),
interaction_fun(std::move(interaction_fun)),
action_fun(std::move(action_fun))
{}

void fun::interactable_t::set_layer(layer_t l) {
    layer = l;
}
