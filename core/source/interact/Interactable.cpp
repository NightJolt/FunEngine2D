#include "interact/interactable.h"

fun::interactable_t::interactable_t(const std::function <bool(vec2f_t)>& interaction_fun, layer_t layer) :
interaction_fun(std::move(interaction_fun)),
layer(layer),
right_pressed(false),
right_hold(false),
right_released(false),
left_pressed(false),
left_hold(false),
left_released(false),
hover_enter(false),
hover_hold(false),
hover_exit(false)
{}