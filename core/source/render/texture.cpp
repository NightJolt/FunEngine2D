#include "render/texture.h"

fun::texture_t::texture_t(sf::Texture* texture, vec2u_t grid_size) :
    m_texture(texture),
    m_grid_size(grid_size)
{
    if (m_texture) m_cell_size = (vec2u_t)m_texture->getSize() / m_grid_size;
}

void fun::texture_t::set_texture(sf::Texture* texture) {
    m_texture = texture;
}

void fun::texture_t::set_grid_size(vec2u_t grid_size) {
    m_grid_size = grid_size;
    m_cell_size = (vec2u_t)m_texture->getSize() / m_grid_size;
}

sf::Texture* fun::texture_t::get_texture() const {
    return m_texture;
}

fun::uint32_t4 fun::texture_t::get_subtexture(uint32_t index) const {
    return { (index % m_grid_size.x) * m_cell_size.x, (index / m_grid_size.x) * m_cell_size.y, m_cell_size.x, m_cell_size.y };
}