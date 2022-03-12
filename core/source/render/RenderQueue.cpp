#include "render/RenderQueue.h"

fun::RenderQueue::RenderItem::RenderItem(const sf::Drawable& d, uint32_t o) : drawable(&d), layer(o) {}

void fun::RenderQueue::Add(const sf::Drawable& drawable, uint32_t layer) {
    queue.emplace_back(drawable, layer);
}

void fun::RenderQueue::Clear() {
    queue.clear();
}

void fun::RenderQueue::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    std::stable_sort(queue.begin(), queue.end(), [](const RenderItem& a, const RenderItem& b) -> bool const { return a.layer < b.layer; });

    for (auto& item : queue) {
        target.draw(*item.drawable, states);
    }
}