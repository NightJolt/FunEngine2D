// #pragma once

#include "../../globals.h"
#include "../../data/gridmap/defs.h"
#include "../texture.h"
#include "../../data/gridmap/gridmap.h"

namespace fun::render {
    template <data::chunk_size_t S>
    class meshmap_t : public sf::Drawable {
    public:
        static constexpr data::chunk_size_t s_chunk_size = S;

    private:
        struct quad_t {
            vertex_t vertices[4];
        };

    public:
        meshmap_t(data::tile_size_t tile_size, texture_t texture) : m_tile_size(tile_size), m_texture(texture) {
            m_gridmap.set_init_chunk([tile_size](data::gridchunk_t<s_chunk_size, quad_t>* chunk, data::chunk_pos_t chunk_pos) {
                vec2f_t position(data::chunk_to_grid(chunk_pos, s_chunk_size));

                for (data::tile_int_t x = 0; x < s_chunk_size; x++) {
                    for (data::tile_int_t y = 0; y < s_chunk_size; y++) {
                        auto& quad = chunk->get_data({ x, y });

                        data::tile_size2d_t tile_pos = data::tile_size2d_t(x, y) * tile_size;

                        quad.vertices[0].position = position + tile_pos * tile_size;
                        quad.vertices[1].position = position + (tile_pos + data::tile_size2d_t { 1.f, 0.f }) * tile_size;
                        quad.vertices[2].position = position + (tile_pos + data::tile_size2d_t { 1.f, 1.f }) * tile_size;
                        quad.vertices[3].position = position + (tile_pos + data::tile_size2d_t { 0.f, 1.f }) * tile_size;
                    }
                }
            });
        }

        ~meshmap_t() noexcept override = default;

        void set_color(data::grid_pos_t grid_pos, rgb_t color) {
            auto& quad = m_gridmap.get_data(grid_pos);

            quad.vertices[0].color = color;
            quad.vertices[1].color = color;
            quad.vertices[2].color = color;
            quad.vertices[3].color = color;
        }

        void set_texture(data::grid_pos_t grid_pos, vec2u_t texture_pos) {
            auto& quad = m_gridmap.get_data(grid_pos);
            auto subtexture = m_texture.get_subtexture(texture_pos);

            quad.vertices[0].texCoords = vec2f_t(subtexture[0], subtexture[1]);
            quad.vertices[1].texCoords = vec2f_t(subtexture[0] + subtexture[2], subtexture[1]);
            quad.vertices[2].texCoords = vec2f_t(subtexture[0] + subtexture[2], subtexture[1] + subtexture[3]);
            quad.vertices[3].texCoords = vec2f_t(subtexture[0], subtexture[1] + subtexture[3]);
        }

    private:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
            states.texture = m_texture.get_texture();

            for (auto& [pos, chunk] : m_gridmap.get_chunks()) {
                target.draw((vertex_t*)chunk->get_data_array(), s_chunk_size * s_chunk_size * 4, sf::Quads, states);
            }
        }

        mutable data::gridmap_t<s_chunk_size, quad_t> m_gridmap;
        data::tile_size_t m_tile_size;
        texture_t m_texture;
    };
}
