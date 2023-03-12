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
        transform_t transform;
        rect_t space;
    };
}

auto fun::gui::create_box() -> ecs::entity_t {
    ecs::entity_t box = ent::create();

    ecs::add_component <box_info_t> (box);

    return box;
}

auto fun::gui::set_transform(ecs::entity_t box, transform_t transform) -> void {
    ecs::get_component <box_info_t> (box).transform = transform;
}

auto fun::gui::free_box(ecs::entity_t box) -> void {
    ecs::remove_component <box_info_t> (box);

    ent::destroy(box);
}

auto fun::gui::create_canvas() -> ecs::entity_t {
    ecs::entity_t box = create_box();
    
    return box;
}

auto fun::gui::free_canvas(ecs::entity_t canvas) -> void {
    ecs::remove_component <box_info_t> (canvas);

    free_box(canvas);
}

auto fun::gui::create_image() -> ecs::entity_t {
    ecs::entity_t box = create_box();

    auto& sprite = ecs::add_component <image_t> (box);
    sprite.set_origin({ 0.5f, 0.5f });

    return box;
}

auto fun::gui::free_image(ecs::entity_t image) -> void {
    ecs::remove_component <image_t> (image);

    free_box(image);
}

void fun::gui::render(ecs::entity_t canvas, render::window_t& window) {
    auto& box_info = ecs::get_component <box_info_t> (canvas);

    box_info.space = rect_t(0, 0, window.get_resoluton().x, window.get_resoluton().y);
    
    for (auto it = ent::children_iterator_t(canvas, true); it.valid(); it.next()) {
        auto parent = ecs::get_component <ent::hierarchy_t> (it.get()).parent;
        auto& pbox = ecs::get_component <box_info_t> (parent);
        auto& box = ecs::get_component <box_info_t> (it.get());

        auto pspace = pbox.space;
        auto& space = box.space;

        auto hsize = (pspace.right - pspace.left) * box.transform.rel_size.x + box.transform.abs_size.x;
        auto vsize = (pspace.bottom - pspace.top) * box.transform.rel_size.y + box.transform.abs_size.y;
        
        auto hpos = (pspace.right - pspace.left) * box.transform.rel_pos.x + box.transform.abs_pos.x;
        auto vpos = (pspace.bottom - pspace.top) * box.transform.rel_pos.y + box.transform.abs_pos.y;

        space.left = pspace.left + hpos - hsize * .5f;
        space.right = pspace.left + hpos + hsize * .5f;
        space.top = pspace.top + vpos - vsize * .5f;
        space.bottom = pspace.top + vpos + vsize * .5f;
    }

    for (auto& sprite : ecs::iterate_component <image_t> ()) {
        auto& box = ecs::get_component <box_info_t> (ecs::get_entity(sprite));

        float hsize = box.space.right - box.space.left;
        float vsize = box.space.bottom - box.space.top;

        sprite.set_position(fun::vec2f_t { box.space.left, box.space.top } + fun::vec2f_t { hsize * .5f, vsize * .5f });
        sprite.set_scale({ hsize, vsize });

        window.draw_ui(sprite, 0);
    }
} 