#pragma once

#include "../../globals.h"
#include "../../vec2.h"

namespace fun::data {
    typedef int32_t grid_int_t;
    typedef int32_t chunk_int_t;
    typedef uint8_t tile_int_t;

    typedef uint32_t chunk_volume_t;

    typedef vec2_t <grid_int_t> grid_pos_t;
    typedef vec2_t <chunk_int_t> chunk_pos_t;
    typedef vec2_t <tile_int_t> tile_pos_t;

    typedef tile_int_t chunk_size_t;
    typedef float tile_size_t;

    typedef vec2_t <chunk_size_t> chunk_size2d_t;
    typedef vec2_t <tile_size_t> tile_size2d_t;

    tile_pos_t index_to_tile(chunk_volume_t, chunk_size_t);
    chunk_volume_t tile_to_index(tile_pos_t, chunk_size_t);

    grid_pos_t world_to_grid(vec2f_t, tile_size_t);
    chunk_pos_t grid_to_chunk(grid_pos_t, chunk_size_t);
    grid_pos_t chunk_to_grid(chunk_pos_t, chunk_size_t);
    tile_pos_t grid_to_tile(grid_pos_t, chunk_size_t);
}