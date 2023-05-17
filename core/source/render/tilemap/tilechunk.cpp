#include "render/tilemap/tilechunk.h"

#include <color.h>

fun::render::tilechunk_t::tilechunk_t(chunk_pos_t chunk_pos, chunk_size_t chunk_size, tile_size_t tile_size) {
    m_pos = chunk_pos;
    m_size = chunk_size;
    m_tile_size = tile_size;
    
    m_primitive.resize(m_size * m_size * 4);
    m_primitive.set_primitive_type(sf::PrimitiveType::Quads);

    vec2f_t position(chunk_to_grid(chunk_pos, chunk_size));

    for (chunk_volume_t i = 0; i < m_primitive.get_size() >> 2; i++) {
        chunk_volume_t ind = i << 2;

        auto& vertex_0 = m_primitive.get_vertex(ind);
        auto& vertex_1 = m_primitive.get_vertex(ind + 1);
        auto& vertex_2 = m_primitive.get_vertex(ind + 2);
        auto& vertex_3 = m_primitive.get_vertex(ind + 3);

        tile_size2d_t tile_pos = (tile_size2d_t)index_to_tile(i, m_size) * m_tile_size;

        vertex_0.position = position + tile_pos * m_tile_size;
        vertex_1.position = position + (tile_pos + tile_size2d_t { 1.f, 0.f }) * m_tile_size;
        vertex_2.position = position + (tile_pos + tile_size2d_t { 1.f, 1.f }) * m_tile_size;
        vertex_3.position = position + (tile_pos + tile_size2d_t { 0.f, 1.f }) * m_tile_size;
    }
}

void fun::render::tilechunk_t::bind_texture(texture_t texture) {
    m_primitive.bind_texture(texture);

    m_texture = texture;
}

void fun::render::tilechunk_t::set_color(tile_pos_t tile_pos, rgb_t color) {
    chunk_volume_t i = tile_to_index(tile_pos, m_size) << 2;

    m_primitive.get_vertex(i).color = color;
    m_primitive.get_vertex(i + 1).color = color;
    m_primitive.get_vertex(i + 2).color = color;
    m_primitive.get_vertex(i + 3).color = color;
}

fun::rgb_t fun::render::tilechunk_t::get_color(tile_pos_t tile_pos) {
    return m_primitive.get_vertex(tile_to_index(tile_pos, m_size)).color;
}

void fun::render::tilechunk_t::set_texture(tile_pos_t tile_pos, vec2u_t texture_pos) {
    chunk_volume_t i = tile_to_index(tile_pos, m_size) << 2;

    auto subtexture = m_texture.get_subtexture(texture_pos);

    m_primitive.get_vertex(i).texCoords = vec2f_t(subtexture[0], subtexture[1]);
    m_primitive.get_vertex(i + 1).texCoords = vec2f_t(subtexture[0] + subtexture[2], subtexture[1]);
    m_primitive.get_vertex(i + 2).texCoords = vec2f_t(subtexture[0] + subtexture[2], subtexture[1] + subtexture[3]);
    m_primitive.get_vertex(i + 3).texCoords = vec2f_t(subtexture[0], subtexture[1] + subtexture[3]);
}

void fun::render::tilechunk_t::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_primitive, states);
}
