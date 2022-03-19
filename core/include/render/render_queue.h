#pragma once

#include "../globals.h"

namespace fun {
    struct render_item_t {
        render_item_t(const sf::Drawable&, uint32_t);

        const sf::Drawable* drawable;
        int layer;
    };

    class render_queue_t : public sf::Drawable {
    public:

        void add(const sf::Drawable&, uint32_t);
        void clear();

    private:

        void draw(sf::RenderTarget&, sf::RenderStates) const override;

        mutable std::vector <render_item_t> queue;
    };
}