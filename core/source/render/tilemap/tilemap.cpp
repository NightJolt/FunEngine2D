#include "render/tilemap/tilemap.h"
#include "render/tilemap/tilechunk.h"

#include <color.h>

fun::render::tilemap_t::tilemap_t(chunk_size_t chunk_size, tile_size_t tile_size) :
    m_chunk_size(chunk_size),
    m_tile_size(tile_size)
{}

fun::render::tilemap_t::~tilemap_t() {
    for (auto& [pos, chunk] : m_tilechunks) {
        delete chunk;
    }
}

void fun::render::tilemap_t::bind_texture(texture_t texture) {
    for (auto& [pos, chunk] : m_tilechunks) {
        chunk->bind_texture(texture);
    }

    m_texture = texture;
}

void fun::render::tilemap_t::set_color(grid_pos_t tile_pos, rgb_t color) {
    get_chunk(grid_to_chunk(tile_pos, m_chunk_size))->set_color(grid_to_tile(tile_pos, m_chunk_size), color);
}

void fun::render::tilemap_t::set_texture(grid_pos_t tile_pos, vec2u_t texture_pos) {
    get_chunk(grid_to_chunk(tile_pos, m_chunk_size))->set_texture(grid_to_tile(tile_pos, m_chunk_size), texture_pos);
}

void fun::render::tilemap_t::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (auto& [pos, chunk] : m_tilechunks) {
        target.draw(*chunk, states);
    }
}

fun::render::tilechunk_t* fun::render::tilemap_t::get_chunk(chunk_pos_t chunk_pos) {
    if (m_tilechunks.contains(chunk_pos)) {
        return m_tilechunks[chunk_pos];
    }

    auto chunk = new tilechunk_t(chunk_pos, m_chunk_size, m_tile_size);
    m_tilechunks[chunk_pos] = chunk;
    chunk->bind_texture(m_texture);

    return chunk;
}
