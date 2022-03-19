#include "interact/interactable.h"

fun::interactable_t::interactable_t(const std::function <bool(vec2f_t)>& interaction_fun, layer_t layer) :
interaction_fun(std::move(interaction_fun)),
layer(layer)
{}
