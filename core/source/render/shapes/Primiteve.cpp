#include "render/shapes/Primitive.h"

fun::Primitive::Primitive(std::vector <sf::Vertex>& vertices, sf::PrimitiveType primitive_type) : m_vertices(std::move(vertices)), m_primitive_type(primitive_type) {}

void fun::Primitive::draw(sf::RenderTarget& render_target, sf::RenderStates render_states) const {
    render_target.draw(&m_vertices[0], m_vertices.size(), m_primitive_type, render_states);
}