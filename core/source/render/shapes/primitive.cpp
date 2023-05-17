#include "render/shapes/primitive.h"


fun::render::vertice_iterator_t::vertice_iterator_t() : begin_p(nullptr), end_p(nullptr), ptr(nullptr) {}

fun::render::vertice_iterator_t::vertice_iterator_t(std::vector <vertex_t>& vertices, size_t n) : begin_p(vertices.data()), end_p(vertices.data() + n), ptr(vertices.data()) {}

fun::render::vertex_t* fun::render::vertice_iterator_t::begin() {
    return begin_p;
}

const fun::render::vertex_t* fun::render::vertice_iterator_t::begin() const {
    return begin_p;
}

fun::render::vertex_t* fun::render::vertice_iterator_t::end() {
    return end_p;
}

const fun::render::vertex_t* fun::render::vertice_iterator_t::end() const {
    return end_p;
}


fun::render::primitive_t::primitive_t(std::vector <vertex_t>& vertices, sf::PrimitiveType primitive_type) : m_vertices(std::move(vertices)), m_primitive_type(primitive_type) {}

void fun::render::primitive_t::bind_texture(texture_t texture) {
    m_texture = texture;
}

void fun::render::primitive_t::set_vertices(const std::vector <vertex_t>& vertices) {
    m_vertices = std::move(vertices);
}

void fun::render::primitive_t::set_primitive_type(sf::PrimitiveType primitive_type) {
    m_primitive_type = primitive_type;
}

void fun::render::primitive_t::resize(uint32_t n) {
    m_vertices.resize(n);
}

uint32_t fun::render::primitive_t::get_size() const {
    return m_vertices.size();
}

fun::render::vertice_iterator_t fun::render::primitive_t::get_iterator() {
    return vertice_iterator_t(m_vertices, m_vertices.size());
}

fun::render::vertice_iterator_t fun::render::primitive_t::get_iterator(uint32_t n) {
    return vertice_iterator_t(m_vertices, n);
}

fun::render::vertex_t& fun::render::primitive_t::get_vertex(uint32_t i) {
    return m_vertices[i];
}

void fun::render::primitive_t::batch(primitive_t& primitive) {
    m_vertices.insert(m_vertices.end(), primitive.m_vertices.begin(), primitive.m_vertices.end());
}

void fun::render::primitive_t::draw(sf::RenderTarget& render_target, sf::RenderStates render_states) const {
    render_states.texture = m_texture.get_texture();
    // render_states.shader = m_shader.get_shader();

    render_target.draw(&m_vertices[0], m_vertices.size(), m_primitive_type, render_states);
}