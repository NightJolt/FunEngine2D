#pragma once

#include "../../globals.h"
#include "defs.h"
#include "../texture.h"

namespace fun::render {
    class tilemap_t : public sf::Drawable {
    private:
        typedef fun::unordered_map_vec2_t <chunk_int_t, tilechunk_t*> tilechunk_map_t;

    public:
        tilemap_t(chunk_size_t, tile_size_t);
        ~tilemap_t() noexcept override;

        void bind_texture(texture_t);

        void set_color(grid_pos_t, rgb_t);
        void set_texture(grid_pos_t, vec2u_t);

    private:
        void draw(sf::RenderTarget&, sf::RenderStates) const override;

        tilechunk_t* get_chunk(chunk_pos_t);

        chunk_size_t m_chunk_size;
        tile_size_t m_tile_size;
        tilechunk_map_t m_tilechunks;

        texture_t m_texture;
    };
}