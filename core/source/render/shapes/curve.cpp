#include "render/shapes/curve.h"

fun::render::shape::curve_t::curve_t() {
    m_primitive.set_primitive_type(sf::PrimitiveType::TrianglesStrip);
}

void fun::render::shape::curve_t::set_width(float width) {
    m_width = width;
    m_update_body = true;
}

void fun::render::shape::curve_t::set_outline_width(float width) {
    m_outline_width = width;
    m_update_body = true;
}

void fun::render::shape::curve_t::set_color(sf::Color color) {
    m_color = color;
    m_update_color = true;
}

void fun::render::shape::curve_t::set_outline_color(sf::Color color) {
    m_outline_color = color;
    m_update_color = true;
}

void fun::render::shape::curve_t::set_points(const std::vector <vec2f_t>& points) {
    m_points = std::move(points);
    m_update_body = true;
}

void fun::render::shape::curve_t::update() const {
    if (m_update_body) {
        update_body();

        m_update_body = false;
    }

    if (m_update_color) {
        update_color();

        m_update_color = false;
    }
}

void fun::render::shape::curve_t::update_body() const {
    std::vector <sf::Vertex> vertices;
    std::vector <sf::Vertex> outline_vertices;

    fun::vec2f_t start = m_points[0];
    fun::vec2f_t end, middle;

    const float half_width = m_width * .5f;

    for (int i = 1; i < m_points.size(); i++) {
        end = m_points[i];

        fun::vec2f_t vec_right = fun::math::swap(fun::math::normalize(end - start));
        fun::vec2f_t vec_left = vec_right * -1.f;

        vertices.emplace_back(start + vec_right * m_width, m_color);
        vertices.emplace_back(end + vec_right * m_width, m_color);
        vertices.emplace_back(start + vec_left * m_width, m_color);
        vertices.emplace_back(end + vec_left * m_width, m_color);

        if (m_outline_width > 0) {
            vertices.emplace_back(start + vec_right * m_outline_width, m_outline_color);
            vertices.emplace_back(end + vec_right * m_outline_width, m_outline_color);
            vertices.emplace_back(start + vec_left * m_outline_width, m_outline_color);
            vertices.emplace_back(end + vec_left * m_outline_width, m_outline_color);
        }

        start = end;
    }
    
    outline_vertices.emplace_back(vertices);
    m_primitive.set_vertices(outline_vertices);
}

void fun::render::shape::curve_t::update_color() const {
    int ind = 0;

    auto& vertices = m_primitive.get_vertices();

    if (m_outline_width > 0) {
        for (; ind < vertices.size() >> 1; ind++) {
            vertices[ind].color = m_outline_color.to_sf();
        }
    }

    for (; ind < vertices.size(); ind++) {
        vertices[ind].color = m_color.to_sf();
    }
}

void fun::render::shape::curve_t::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    update();

    target.draw(m_primitive, states);
}
