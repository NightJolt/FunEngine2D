#include "render/Drawable.h"

fun::Drawable::~Drawable() noexcept = default;

void fun::Drawable::Drawable_SetDrawingLayer(uint32_t new_layer) {
    layer = new_layer;
}

uint32_t fun::Drawable::Drawable_GetDrawingLayer() const {
    return layer;
}