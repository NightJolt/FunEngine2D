#pragma once

#include "../Globals.h"

namespace fun {
    class RenderQueue : public sf::Drawable {
    public:

        void Add(const sf::Drawable&, uint32_t);
        void Clear();

    private:

        struct RenderItem {
            RenderItem(const sf::Drawable&, uint32_t);

            const sf::Drawable* drawable;
            int layer;
        };

        void draw(sf::RenderTarget&, sf::RenderStates) const override;

        mutable std::vector <RenderItem> queue;
    };
}