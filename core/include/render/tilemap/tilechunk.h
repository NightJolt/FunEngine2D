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

        void set_tile(tile_pos_t, uint32_t);
        uint32_t get_tile(tile_pos_t) const;

        void set_color(tile_pos_t, rgb_t);
        rgb_t get_color(tile_pos_t) const;

    private:
        void draw(sf::RenderTarget&, sf::RenderStates) const override;

        chunk_pos_t m_pos;
        chunk_size_t m_size;
        chunk_size_t m_tile_size;
        
        primitive_t m_primitive;
    };
}