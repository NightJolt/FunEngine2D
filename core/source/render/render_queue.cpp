#include "render/render_queue.h"

fun::render_item_t::render_item_t(const sf::Drawable& d, uint32_t o) : drawable(&d), layer(o) {}

void fun::render_queue_t::add(const sf::Drawable& drawable, uint32_t layer) {
    queue.emplace_back(drawable, layer);
}

void fun::render_queue_t::clear() {
    queue.clear();
}

void fun::render_queue_t::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    std::stable_sort(queue.begin(), queue.end(), [](const render_item_t& a, const render_item_t& b) -> bool const { return a.layer < b.layer; });

    for (auto& item : queue) {
        target.draw(*item.drawable, states);
    }
}