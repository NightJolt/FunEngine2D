#include "render/shapes/primitive.h"

fun::primitive_t::primitive_t(std::vector <sf::Vertex>& vertices, sf::PrimitiveType primitive_type) : m_vertices(std::move(vertices)), m_primitive_type(primitive_type) {}

std::vector <sf::Vertex>& fun::primitive_t::get_vertices() {
    return m_vertices;
}

void fun::primitive_t::set_vertices(const std::vector <sf::Vertex>& vertices) {
    m_vertices = std::move(vertices);
}

void fun::primitive_t::set_primitive_type(sf::PrimitiveType primitive_type) {
    m_primitive_type = primitive_type;
}

void fun::primitive_t::batch(primitive_t& primitive) {
    m_vertices.insert(m_vertices.end(), primitive.m_vertices.begin(), primitive.m_vertices.end());
}

void fun::primitive_t::draw(sf::RenderTarget& render_target, sf::RenderStates render_states) const {
    render_target.draw(&m_vertices[0], m_vertices.size(), m_primitive_type, render_states);
}