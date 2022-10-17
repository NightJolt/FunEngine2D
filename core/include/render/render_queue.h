#pragma once

#include "../globals.h"

namespace fun::render {
    struct render_item_t {
        render_item_t(const sf::Drawable&, layer_t, sf::RenderStates);

        const sf::Drawable* drawable;
        layer_t layer;
        sf::RenderStates render_states;
    };

    class render_queue_t : public sf::Drawable {
    public:

        void add(const sf::Drawable&, layer_t, const sf::RenderStates&);
        void clear();

    private:

        void draw(sf::RenderTarget&, sf::RenderStates) const override;

        mutable std::vector <render_item_t> queue;
    };
}