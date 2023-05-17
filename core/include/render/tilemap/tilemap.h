#pragma once

#include "../../globals.h"
#include "defs.h"

namespace fun::render {
    class tilemap_t : public sf::Drawable {
    public:
        tilemap_t();
        ~tilemap_t();

    private:
        void draw(sf::RenderTarget&, sf::RenderStates) const override;
    };
}