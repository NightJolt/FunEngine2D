#pragma once

#include "../globals.h"

namespace fun {
    class RenderQueue : public sf::Drawable {
    public:

        void Add(const sf::Drawable&, int);
        void Clear();

    private:

        struct RenderItem {
            RenderItem(const sf::Drawable&, int);

            const sf::Drawable* drawable;
            int order;
        };

        void draw(sf::RenderTarget&, sf::RenderStates) const override;

        mutable std::vector <RenderItem> queue;
    };
}