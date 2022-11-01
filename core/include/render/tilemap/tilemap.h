#pragma once

#include "../../globals.h"
#include "defs.h"

namespace fun::render {
    template <tile_int_t W, tile_int_t H>
    class tilemap_t : public sf::Drawable {
    public:
        tilemap_t();
        ~tilemap_t();

    private:
        void draw(sf::RenderTarget&, sf::RenderStates) const override;
    };
}