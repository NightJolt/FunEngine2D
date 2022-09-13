#include "render/shapes/curve.h"

fun::render::shape::curve_t::curve_t() : m_width(1), m_color(rgba_t::white), is_closed(false), m_update_body(false), m_update_color(false) {
    m_primitive.set_primitive_type(sf::PrimitiveType::TrianglesStrip);
}

void fun::render::shape::curve_t::set_width(float width) {
    m_width = width;
    m_update_body = true;
}

void fun::render::shape::curve_t::set_color(rgba_t color) {
    m_color = color;
    m_update_color = true;
}

void fun::render::shape::curve_t::set_points(const std::vector <vec2f_t>& points) {
    m_points = std::move(points);
    m_update_body = true;
}

void fun::render::shape::curve_t::set_closed(bool closed) {
    is_closed = closed;
    m_update_body = true;
}

void fun::render::shape::curve_t::update_body() const {
    std::vector <sf::Vertex> vertices;

    vertices.resize(m_points.size() * 2);

    const float half_width = m_width * .5f;
    const auto color = m_color.to_sf();

    for (int i = 0; i < m_points.size(); i++) {
        fun::vec2f_t right_vec;

        if (!is_closed && i == 0) {
            right_vec = fun::math::rot_270(fun::math::normalize(m_points[1] - m_points[0])) * half_width;
        } else if (!is_closed && i == m_points.size() - 1) {
            right_vec = fun::math::rot_270(fun::math::normalize(m_points[i] - m_points[i - 1])) * half_width;
        } else {
            const auto back = fun::math::normalize(m_points[i - 1] - m_points[i]);
            const auto front = fun::math::normalize(m_points[i + 1] - m_points[i]);

            right_vec = fun::math::bisector(back, front) * half_width;

            if (fun::math::magnitude(back + front) < 0.0001f) {
                right_vec = fun::math::rot_270(fun::math::normalize(m_points[i] - m_points[i - 1])) * half_width;
            } else {
                right_vec = fun::math::bisector(back, front) * -1.f * half_width;

                if (fun::math::dot(fun::math::rot_270(back), front) < 0.f) {
                    right_vec = fun::math::rot_180(right_vec);
                }
            }
        }

        vertices[i * 2].position = (m_points[i] + right_vec).to_sf();
        vertices[i * 2 + 1].position = (m_points[i] - right_vec).to_sf();

        vertices[i * 2].color = color;
        vertices[i * 2 + 1].color = color;
    }
    
    m_primitive.set_vertices(vertices);
}

void fun::render::shape::curve_t::update_color() const {
    const auto color = m_color.to_sf();

    for (auto& vertex : m_primitive.get_vertices()) {
        vertex.color = color;
    }
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

void fun::render::shape::curve_t::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    update();

    target.draw(m_primitive, states);
}
