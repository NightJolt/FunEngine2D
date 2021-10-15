#include "render/Drawable.h"

fun::Drawable::~Drawable() noexcept = default;

void fun::Drawable::Drawable_SetDrawingLayer(i32 new_layer) {
    layer = new_layer;
}

i32 fun::Drawable::Drawable_GetDrawingLayer() const {
    return layer;
}
