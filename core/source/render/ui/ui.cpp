#include "render/ui/ui.h"
#include "ecs/ent.h"
#include "render/window/window.h"

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
        bool dirty;
        layer_t layer;
    };
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

auto fun::gui::create_text() -> ecs::entity_t {
    ecs::entity_t box = create_box();
    
    ecs::add_component <text_t> (box);

    return box;
}

auto fun::gui::free_text(ecs::entity_t text) -> void {
    ecs::remove_component <text_t> (text);

    free_box(text);
}

auto fun::gui::create_button(const action_fun_t& action_fun) -> ecs::entity_t {
    ecs::entity_t box = create_box();

    auto& sprite = ecs::add_component <image_t> (box);
    sprite.set_origin({ 0.5f, 0.5f });

    auto& interactable = ecs::add_component <interactable_t> (box,
        [box](vec2f_t mouse_world_pos, vec2f_t mouse_screen_pos) -> interact_result_t {
            auto space = ecs::get_component <box_info_t> (box).space;

            return {
                mouse_screen_pos.x >= space.left &&
                mouse_screen_pos.x <= space.right &&
                mouse_screen_pos.y >= space.top &&
                mouse_screen_pos.y <= space.bottom,
                mouse_screen_pos - vec2f_t(space.left + (space.right - space.left) * .5f, space.top + (space.bottom - space.top) * .5f)
            };
        },
        action_fun
    );

    return box;
}

auto fun::gui::free_button(ecs::entity_t button) -> void {
    ecs::remove_component <image_t> (button);
    ecs::remove_component <interactable_t> (button);

    free_box(button);
}

auto fun::gui::set_transform(ecs::entity_t box, transform_t transform) -> void {
    auto& box_info = ecs::get_component <box_info_t> (box);

    box_info.transform = transform;
    box_info.dirty = true;
}

auto fun::gui::set_layer(ecs::entity_t box, layer_t layer) -> void {
    auto& box_info = ecs::get_component <box_info_t> (box);

    box_info.layer = layer;

    if (ecs::has_component <interactable_t> (box)) {
        ecs::get_component <interactable_t> (box).set_layer(layer);
    }
}

void fun::gui::set_dirty(ecs::entity_t box) {
    auto& box_info = ecs::get_component <box_info_t> (box);

    box_info.dirty = true;
}

void fun::gui::force_repaint(render::window_t& window) {
    window.invalidate_ui();
}

void fun::gui::render(ecs::entity_t canvas, render::window_t& window) {
    auto& box_info = ecs::get_component <box_info_t> (canvas);

    box_info.space = rect_t(0, 0, window.get_resoluton().x, window.get_resoluton().y);
    
    for (auto it = ent::children_iterator_t(canvas, true); it.valid(); it.next()) {
        auto parent = ecs::get_component <ent::hierarchy_t> (it.get()).parent;
        auto& pbox = ecs::get_component <box_info_t> (parent);
        auto& box = ecs::get_component <box_info_t> (it.get());

        if (!(box.dirty |= pbox.dirty)) continue;

        auto pspace = pbox.space;
        auto& space = box.space;

        float32_t axis_size_x = pspace.right - pspace.left;
        float32_t axis_size_y = pspace.bottom - pspace.top;

        float32_t axis_sizes[] = {
            axis_size_x,
            axis_size_y,
            std::min(axis_size_x, axis_size_y),
            std::max(axis_size_x, axis_size_y)
        };

        auto hsize = axis_sizes[box.transform.scaling_axis[0]] * box.transform.rel_size.x + box.transform.abs_size.x;
        auto vsize = axis_sizes[box.transform.scaling_axis[1]] * box.transform.rel_size.y + box.transform.abs_size.y;
        
        auto hpos = (axis_size_x - hsize) * box.transform.rel_pos.x + box.transform.abs_pos.x + hsize * .5f;
        auto vpos = (axis_size_y - vsize) * box.transform.rel_pos.y + box.transform.abs_pos.y + vsize * .5f;

        space.left = pspace.left + hpos - hsize * .5f;
        space.right = pspace.left + hpos + hsize * .5f;
        space.top = pspace.top + vpos - vsize * .5f;
        space.bottom = pspace.top + vpos + vsize * .5f;
    }

    for (auto& sprite : ecs::iterate_component <image_t> ()) {
        auto& box = ecs::get_component <box_info_t> (ecs::get_entity(sprite));

        if (box.dirty) {
            float hsize = box.space.right - box.space.left;
            float vsize = box.space.bottom - box.space.top;

            sprite.set_position(vec2f_t { box.space.left, box.space.top } + vec2f_t { hsize * .5f, vsize * .5f });
            sprite.set_scale({ hsize, vsize });
        }

        window.draw_ui(sprite, box.layer);
    }

    for (auto& text : ecs::iterate_component <text_t> ()) {
        auto& box = ecs::get_component <box_info_t> (ecs::get_entity(text));

        if (box.dirty) {
            float hsize = box.space.right - box.space.left;
            float vsize = box.space.bottom - box.space.top;

            text.setPosition((vec2f_t { box.space.left, box.space.top } + vec2f_t { hsize * .5f, vsize * .5f }).to_sf());

            float x_ratio = hsize / text.getLocalBounds().width;
            float y_ratio = vsize / text.getLocalBounds().height;
            float ratio = std::min(x_ratio, y_ratio);

            text.setScale(ratio, ratio);
            text.move(
                text.getPosition().x - text.getGlobalBounds().left - text.getGlobalBounds().width * .5f,
                text.getPosition().y - text.getGlobalBounds().top - text.getGlobalBounds().height * .5f
            );
        }

        window.draw_ui(text, box.layer);
    }

    bool should_invalidate_ui = box_info.dirty;
    box_info.dirty = false;
    
    for (auto it = ent::children_iterator_t(canvas, true); it.valid(); it.next()) {
        auto& box = ecs::get_component <box_info_t> (it.get());
        
        should_invalidate_ui |= box.dirty;

        box.dirty = false;
    }

    if (should_invalidate_ui) window.invalidate_ui();
}