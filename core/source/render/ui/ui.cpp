#include "render/ui/ui.h"
#include "ecs/ent.h"

namespace fun::gui {
    struct rect_t {
        rect_t() : left(0), top(0), right(0), bottom(0) {}
        rect_t(float32_t v) : left(v), top(v), right(v), bottom(v) {}
        rect_t(float32_t h, float32_t v) : left(v), top(h), right(v), bottom(h) {}
        rect_t(float32_t l, float32_t t, float32_t r, float32_t b) : left(l), top(t), right(r), bottom(b) {}

        float32_t left;
        float32_t top;
        float32_t right;
        float32_t bottom;
    };

    struct box_info_t {
        vec2f_t abs_size;
        vec2f_t rel_size;

        vec2f_t abs_pos;
        vec2f_t rel_pos;

        rect_t space;
    };

    CREATE_TYPE_FROM_NONPRIMITIVE(image_t, render::sprite_t)
}

namespace fun::gui {
    auto get_inner_space(ecs::entity_t box) -> rect_t {
        return ecs::get_component <box_info_t> (box).space;
    }
}

auto fun::gui::create_box() -> ecs::entity_t {
    ecs::entity_t box = ent::create();

    ecs::add_component <box_info_t> (box);

    return box;
}

auto fun::gui::free_box(ecs::entity_t box) -> void {
    ecs::remove_component <box_info_t> (box);

    ent::destroy(box);
}

auto fun::gui::create_canvas(vec2f_t size) -> ecs::entity_t {
    ecs::entity_t box = create_box();

    auto& box_info = ecs::get_component <box_info_t> (box);

    box_info.abs_size = size;
    box_info.rel_size = 0;
    
    return box;
}

auto fun::gui::free_canvas(ecs::entity_t canvas) -> void {
    ecs::remove_component <box_info_t> (canvas);

    free_box(canvas);
}

auto fun::gui::create_image() -> ecs::entity_t {
    ecs::entity_t box = create_box();

    auto& sprite = ecs::add_component <image_t> (box);

    return box;
}

auto fun::gui::free_image(ecs::entity_t image) -> void {
    ecs::remove_component <image_t> (image);

    free_box(image);
}

void fun::gui::render(ecs::entity_t canvas, render::window_t& window) {
    auto& box_info = ecs::get_component <box_info_t> (canvas);
    
    for (auto it = ent::children_iterator_t(canvas, true); it.valid(); it.next()) {
        if (!ecs::has_component <image_t> (it.get())) continue;

        auto box = it.get();
        auto& sprite = ecs::get_component <image_t> (box);

        // sprite.set_scale(get_inner_space(box));
        // sprite.set_position(get_position(box));

        window.draw_world(sprite, 0);
    }
} 