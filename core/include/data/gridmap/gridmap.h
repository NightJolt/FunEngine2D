#pragma once

#include "../../globals.h"
#include "defs.h"
#include "gridchunk.h"

namespace fun::data {
    template <chunk_size_t S, class T>
    class gridmap_t {
    public:
        static constexpr chunk_size_t chunk_size = S;
        typedef T tile_data_t;

    private:
        typedef unordered_map_vec2_t <chunk_int_t, gridchunk_t<S, T>*> gridchunk_map_t;
        typedef fn_t<void(gridchunk_t<S, T>*, chunk_pos_t)> init_chunk_t;

    public:
        ~gridmap_t() {
            for (auto& [pos, chunk] : m_gridchunks) {
                delete chunk;
            }
        }

        tile_data_t& get_data(grid_pos_t grid_pos) {
            return get_chunk(grid_to_chunk(grid_pos, S))->get_data(grid_to_tile(grid_pos, S));
        }

        tile_data_t* get_data_unforced(grid_pos_t grid_pos) {
            if (!m_gridchunks.contains(grid_to_chunk(grid_pos, S))) {
                return nullptr;
            }

            return &get_chunk(grid_to_chunk(grid_pos, S))->get_data(grid_to_tile(grid_pos, S));
        }

        tile_data_t* get_data_array(grid_pos_t grid_pos) {
            return get_chunk(grid_to_chunk(grid_pos, S))->get_data_array();
        }

        gridchunk_map_t& get_chunks() {
            return m_gridchunks;
        }

        void set_init_chunk(init_chunk_t init_chunk) {
            m_init_chunk = init_chunk;
        }

    private:
        gridchunk_t<S, T>* get_chunk(chunk_pos_t chunk_pos) {
            if (m_gridchunks.contains(chunk_pos)) {
                return m_gridchunks[chunk_pos];
            }

            auto* chunk = new gridchunk_t<chunk_size, tile_data_t>();
            m_gridchunks[chunk_pos] = chunk;

            if (m_init_chunk) {
                m_init_chunk(chunk, chunk_pos);
            }

            return chunk;
        }
        
        gridchunk_map_t m_gridchunks;
        init_chunk_t m_init_chunk;
    };
}