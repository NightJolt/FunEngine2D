#pragma once

#include "../../globals.h"
#include "defs.h"
#include "../texture.h"
#include "../shapes/primitive.h"

namespace fun::render {
    class tilechunk_t : public sf::Drawable {
    public:
        tilechunk_t(chunk_pos_t, chunk_size_t, tile_size_t);
        ~tilechunk_t() noexcept override = default;

        void bind_texture(texture_t);

        void set_color(tile_pos_t, rgb_t);
        rgb_t get_color(tile_pos_t);

        void set_texture(tile_pos_t, vec2u_t);

    private:
        void draw(sf::RenderTarget&, sf::RenderStates) const override;

        chunk_pos_t m_pos;
        chunk_size_t m_size;
        tile_size_t m_tile_size;
        
        primitive_t m_primitive;
        texture_t m_texture;
    };
}