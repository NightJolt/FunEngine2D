#pragma once

typedef unsigned int uint32_t;
typedef unsigned char uint8_t;

typedef uint8_t channel_t;
struct color_t {
    channel_t r;
    channel_t g;
    channel_t b;
};

void create_texture(color_t** texture, uint32_t width, uint32_t height);
void free_texture(color_t* texture);
void fill_texture(color_t* texture, uint32_t width, uint32_t height, color_t color);

void create_surface(color_t** surface, uint32_t width, uint32_t height);
void free_surface(color_t* surface);

void texture_to_surface(color_t* surface, color_t* texture, uint32_t width, uint32_t height);
void surface_to_texture(color_t* texture, color_t* surface, uint32_t width, uint32_t height);

void blit_texture(
    color_t* target_texture,
    color_t* source_texture,
    channel_t* mask,
    uint32_t target_x,
    uint32_t target_y,
    uint32_t target_w,
    uint32_t target_h,
    uint32_t source_x,
    uint32_t source_y,
    uint32_t source_w,
    uint32_t source_h
);