#pragma once

#include "../../globals.h"
#include "../../color.h"
#include "../../data/gridmap/defs.h"
#include "../texture.h"
#include "../../data/gridmap/gridmap.h"
#include "../window/window_manager.h"
#include "../window/window.h"

namespace fun::render {
    template <data::chunk_size_t C, data::tile_size_t T>
    class meshmap_t : public sf::Drawable {
    private:
        struct quad_t {
            vertex_t vertices[4];
        };

    public:
        static constexpr data::chunk_size_t s_chunk_size = C;
        typedef data::gridchunk_t<s_chunk_size, quad_t> chunk_t;
        static constexpr data::tile_size_t s_tile_size = T;

    public:
        explicit meshmap_t(texture_t texture, fun::rgb_t fill_color) : m_texture(texture), m_default_color(fill_color) {
            m_gridmap.set_init_chunk([fill_color](chunk_t* chunk, data::chunk_pos_t chunk_pos) {
                vec2f_t position((vec2f_t)data::chunk_to_grid(chunk_pos, s_chunk_size) * s_tile_size);

                for (data::tile_int_t x = 0; x < s_chunk_size; x++) {
                    for (data::tile_int_t y = 0; y < s_chunk_size; y++) {
                        auto& quad = chunk->get_data({ x, y });

                        data::tile_size2d_t tile_pos = data::tile_size2d_t(x, y) * s_tile_size;

                        quad.vertices[0].position = position + tile_pos;
                        quad.vertices[1].position = position + tile_pos + data::tile_size2d_t { s_tile_size, 0.f };
                        quad.vertices[2].position = position + tile_pos + data::tile_size2d_t { s_tile_size, s_tile_size };
                        quad.vertices[3].position = position + tile_pos + data::tile_size2d_t { 0.f, s_tile_size };

                        quad.vertices[0].color = fill_color;
                        quad.vertices[1].color = fill_color;
                        quad.vertices[2].color = fill_color;
                        quad.vertices[3].color = fill_color;
                    }
                }
            });
        }

        ~meshmap_t() noexcept override = default;

        rgb_t get_color(data::grid_pos_t grid_pos) {
            auto* quad = m_gridmap.get_data(grid_pos);

            return quad ? rgb_t { quad->vertices[0].color } : m_default_color;
        }

        rgb_t get_or_create_color(data::grid_pos_t grid_pos) {
            auto* quad = m_gridmap.get_or_create_data(grid_pos);

            return quad->vertices[0].color;
        }

        void set_color(data::grid_pos_t grid_pos, rgb_t color) {
            auto* quad = m_gridmap.get_or_create_data(grid_pos);

            quad->vertices[0].color = color;
            quad->vertices[1].color = color;
            quad->vertices[2].color = color;
            quad->vertices[3].color = color;
        }

        void set_color(data::grid_pos_t grid_pos, rgb_t4 color) {
            auto* quad = m_gridmap.get_data(grid_pos);

            quad->vertices[0].color = color[0];
            quad->vertices[1].color = color[1];
            quad->vertices[2].color = color[2];
            quad->vertices[3].color = color[3];
        }

        void set_texture(data::grid_pos_t grid_pos, vec2u_t texture_pos) {
            auto* quad = m_gridmap.get_or_create_data(grid_pos);
            auto subtexture = m_texture.get_subtexture(texture_pos);

            quad->vertices[0].texCoords = vec2f_t(subtexture[0], subtexture[1]);
            quad->vertices[1].texCoords = vec2f_t(subtexture[0] + subtexture[2], subtexture[1]);
            quad->vertices[2].texCoords = vec2f_t(subtexture[0] + subtexture[2], subtexture[1] + subtexture[3]);
            quad->vertices[3].texCoords = vec2f_t(subtexture[0], subtexture[1] + subtexture[3]);
        }

        chunk_t* get_chunk(data::chunk_pos_t chunk_pos) {
            return m_gridmap.get_chunk(chunk_pos);
        }

        chunk_t* get_or_create_chunk(data::chunk_pos_t chunk_pos) {
            return m_gridmap.get_or_create_chunk(chunk_pos);
        }

    private:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
            states.texture = m_texture.get_texture();

            window_t& window = winmgr::get_main_window();

            auto start = fun::data::grid_to_chunk(fun::data::world_to_grid(window.screen_to_world({ 0, 0 }), s_tile_size), s_chunk_size);
            auto end = fun::data::grid_to_chunk(fun::data::world_to_grid(window.screen_to_world(window.get_resoluton()), s_tile_size), s_chunk_size);

            for (data::chunk_int_t x = start.x; x <= end.x; x++) {
                for (data::chunk_int_t y = start.y; y <= end.y; y++) {
                    auto chunk = m_gridmap.get_chunk({ x, y });

                    if (chunk == nullptr) {
                        continue;
                    }

                    target.draw((vertex_t*)chunk->get_data_array(), s_chunk_size * s_chunk_size * 4, sf::Quads, states);
                }
            }
        }

        mutable data::gridmap_t<s_chunk_size, quad_t> m_gridmap;
        texture_t m_texture;
        rgb_t m_default_color;
    };
}
