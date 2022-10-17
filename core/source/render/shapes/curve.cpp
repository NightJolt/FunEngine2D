#include "render/shapes/curve.h"
#include "_math.h"

fun::render::curve_t::curve_t() : m_width(1), m_color(rgba_t::white), m_is_closed(false), m_update_body(false), m_update_color(false) {
    m_primitive.set_primitive_type(sf::PrimitiveType::TrianglesStrip);
}

void fun::render::curve_t::set_width(float width) {
    m_width = width;
    m_update_body = true;
}

void fun::render::curve_t::set_color(rgba_t color) {
    m_color = color;
    m_update_color = true;
}

void fun::render::curve_t::set_points(const std::vector <vec2f_t>& points) {
    m_points = std::move(points);
    m_update_body = true;
}

void fun::render::curve_t::set_closed(bool closed) {
    m_is_closed = closed;
    m_update_body = true;
}

void fun::render::curve_t::update_body() const {
    std::vector <sf::Vertex> vertices;

    const uint32_t points_count = m_points.size();

    vertices.resize((points_count + m_is_closed) * 2);

    const float half_width = m_width * .5f;
    const auto color = m_color.to_sf();

    for (int32_t i = 0; i < points_count; i++) {
        fun::vec2f_t right_vec;

        int32_t cur_i = i;

        if (!m_is_closed && cur_i == 0) {
            right_vec = fun::math::rot_270(fun::math::normalize(m_points[1] - m_points[0])) * half_width;
        } else if (!m_is_closed && cur_i == m_points.size() - 1) {
            right_vec = fun::math::rot_270(fun::math::normalize(m_points[cur_i] - m_points[cur_i - 1])) * half_width;
        } else {
            int32_t prev_i = i == 0? points_count - 1 : i - 1;
            int32_t next_i = i == points_count - 1? 0 : i + 1;

            const auto back = fun::math::normalize(m_points[prev_i] - m_points[cur_i]);
            const auto front = fun::math::normalize(m_points[next_i] - m_points[cur_i]);

            right_vec = fun::math::bisector(back, front) * half_width;

            if (fun::math::magnitude(back + front) < 0.0001f) {
                right_vec = fun::math::rot_270(fun::math::normalize(m_points[cur_i] - m_points[prev_i])) * half_width;
            } else {
                right_vec = fun::math::bisector(back, front) * -1.f * half_width;

                if (fun::math::dot(fun::math::rot_270(back), front) < 0.f) {
                    right_vec = fun::math::rot_180(right_vec);
                }
            }
        }

        vertices[i * 2].position = (m_points[cur_i] + right_vec).to_sf();
        vertices[i * 2 + 1].position = (m_points[cur_i] - right_vec).to_sf();

        vertices[i * 2].color = color;
        vertices[i * 2 + 1].color = color;
    }

    if (m_is_closed) {
        vertices[vertices.size() - 2].position = vertices[0].position;
        vertices[vertices.size() - 1].position = vertices[1].position;

        vertices[vertices.size() - 2].color = color;
        vertices[vertices.size() - 1].color = color;
    }
    
    m_primitive.set_vertices(vertices);
}

void fun::render::curve_t::update_color() const {
    const auto color = m_color.to_sf();

    for (auto& vertex : m_primitive.get_vertices()) {
        vertex.color = color;
    }
}

void fun::render::curve_t::update() const {
    if (m_update_body) {
        update_body();

        m_update_body = false;
    }

    if (m_update_color) {
        update_color();

        m_update_color = false;
    }
}

void fun::render::curve_t::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    update();

    target.draw(m_primitive, states);
}
