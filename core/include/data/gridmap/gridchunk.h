#pragma once

#include "../../globals.h"
#include "defs.h"

namespace fun::data {
    template <chunk_size_t S, class T>
    class gridchunk_t {
    public:
        static constexpr chunk_size_t chunk_size = S;
        typedef T tile_data_t;

    public:
        tile_data_t& get_data(tile_pos_t tile_pos) {
            return m_data[tile_pos.x][tile_pos.y];
        }

        tile_data_t* get_data_array() {
            return &m_data[0][0];
        }

    private:
        tile_data_t m_data[chunk_size][chunk_size];
    };
}