#include "render/tilemap/tilechunk.h"

fun::render::tilechunk_t::tilechunk_t(chunk_pos_t chunck_pos, chunk_size_t chunk_size, tile_size_t tile_size) {
    // m_pos = chunck_pos;
    // m_size = chunk_size;
    // m_tile_size = tile_size;
    
    // .resize(m_size * m_size * 4);
}

void fun::render::tilechunk_t::bind_texture(texture_t texture) {
    m_primitive.bind_texture(texture);
}