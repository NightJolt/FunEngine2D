#include "data/gridmap/defs.h"

#include <_math.h>

fun::data::tile_pos_t fun::data::index_to_tile(tile_index_t i, chunk_size_t chunk_size) {
    return tile_pos_t { (tile_int_t)(i / chunk_size), (tile_int_t)(i % chunk_size) };
}

fun::data::tile_index_t fun::data::tile_to_index(tile_pos_t tile, chunk_size_t chunk_size) {
    return tile.x * chunk_size + tile.y;
}

fun::data::grid_pos_t fun::data::world_to_grid(vec2f_t world_pos, tile_size_t tile_size) {
    world_pos /= (float)tile_size;

    return grid_pos_t { (grid_int_t)(world_pos.x - (world_pos.x < 0)), (grid_int_t)(world_pos.y - (world_pos.y < 0)) };
}

fun::data::chunk_pos_t fun::data::grid_to_chunk(grid_pos_t grid_pos, chunk_size_t chunk_size) {
    chunk_int_t x = grid_pos.x + (grid_pos.x < 0);
    chunk_int_t y = grid_pos.y + (grid_pos.y < 0);
    
    x /= chunk_size;
    y /= chunk_size;

    x -= grid_pos.x < 0;
    y -= grid_pos.y < 0;

    return chunk_pos_t { x, y };
}

fun::data::grid_pos_t fun::data::chunk_to_grid(chunk_pos_t chunk_pos, chunk_size_t chunk_size) {
    return chunk_pos * (chunk_int_t)chunk_size;
}

fun::data::tile_pos_t fun::data::grid_to_tile(grid_pos_t p, chunk_size_t chunk_size) {
    return tile_pos_t { (tile_int_t)math::mod(p.x, chunk_size), (tile_int_t)math::mod(p.y, chunk_size) };
}