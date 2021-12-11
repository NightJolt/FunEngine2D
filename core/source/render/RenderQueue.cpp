#include "render/RenderQueue.h"

fun::RenderQueue::RenderItem::RenderItem(const sf::Drawable& d, int o) : drawable(&d), order(o) {}

void fun::RenderQueue::Add(const sf::Drawable &drawable, int order) {
    queue.emplace_back(drawable, order);
}

void fun::RenderQueue::Clear() {
    queue.clear();
}

void fun::RenderQueue::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    std::stable_sort(queue.begin(), queue.end(), [](const RenderItem& a, const RenderItem& b) -> bool { return a.order < b.order; });

    for (auto& item : queue) {
        target.draw(*item.drawable, states);
    }
}