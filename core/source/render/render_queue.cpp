#include "render/render_queue.h"

fun::render::render_item_t::render_item_t(const sf::Drawable& d, layer_t l, sf::RenderStates rs) : drawable(&d), layer(l), render_states(rs) {}

void fun::render::render_queue_t::add(const sf::Drawable& drawable, layer_t layer, const sf::RenderStates& render_states) {
    queue.emplace_back(drawable, layer, render_states);
}

void fun::render::render_queue_t::clear() {
    queue.clear();
}

void fun::render::render_queue_t::draw(sf::RenderTarget& render_target, sf::RenderStates render_states) const {
    std::stable_sort(queue.begin(), queue.end(), [](const render_item_t& a, const render_item_t& b) -> bool const { return a.layer < b.layer; });

    for (auto& item : queue) {
        render_target.draw(*item.drawable, item.render_states);
    }
}