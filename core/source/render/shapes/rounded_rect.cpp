#include "render/shapes/rounded_rect.h"

fun::rounded_rect_t::rounded_rect_t() {
    build();
}

void fun::rounded_rect_t::set_raidus(float r) {
    if (radius == r) return;

    radius = r;

    should_update = true;
}

void fun::rounded_rect_t::set_position(vec2f_t p) {
    if (position == p) return;

    auto delta = p - position;

    for (auto& point : points) {
        point.position += delta.to_sf();
    }

    position = p;
}

fun::vec2f_t fun::rounded_rect_t::get_position() const {
    return position;
}

void fun::rounded_rect_t::set_size(vec2f_t s) {
    if (size == s) return;

    size = s;

    should_update = true;
}

fun::vec2f_t fun::rounded_rect_t::get_size() const {
    return size;
}

void fun::rounded_rect_t::set_smoothness(int s) {
    if (smoothness == s) return;

    smoothness = s;

    should_update = true;
}

void fun::rounded_rect_t::set_fill_color(sf::Color c) {
    if (color == c) return;

    color = c;

    should_update = true;
}

void fun::rounded_rect_t::build() const {
    points.resize(10 + 4 * smoothness);

    points[0].position = { 0, 0 };

    int ind = 0;
    vec2f_t half_size = size * .5f;
    float angle_step = math::radians(90) / (smoothness + 1);
    float angle;
    sf::Vector2f pos;

    points[++ind].position = { -half_size.x, -half_size.y + radius };

    angle = 0;
    pos = points[ind].position + sf::Vector2f(radius, 0);
    for (int i = 0; i <= smoothness; i++) {
        angle += angle_step;

        points[++ind].position = pos - radius * sf::Vector2f(std::cos(angle), std::sin(angle));
    }

    points[++ind].position = { half_size.x - radius, -half_size.y};

    angle = 0;
    pos = points[ind].position + sf::Vector2f(0, radius);
    for (int i = 0; i <= smoothness; i++) {
        angle += angle_step;

        points[++ind].position = pos + radius * sf::Vector2f(std::sin(angle), -std::cos(angle));
    }

    points[++ind].position = { half_size.x, half_size.y - radius };

    angle = 0;
    pos = points[ind].position + sf::Vector2f(-radius, 0);
    for (int i = 0; i <= smoothness; i++) {
        angle += angle_step;

        points[++ind].position = pos + radius * sf::Vector2f(std::cos(angle), std::sin(angle));
    }

    points[++ind].position = { -half_size.x + radius, half_size.y };

    angle = 0;
    pos = points[ind].position + sf::Vector2f(0, -radius);
    for (int i = 0; i <= smoothness; i++) {
        angle += angle_step;

        points[++ind].position = pos - radius * sf::Vector2f(std::sin(angle), -std::cos(angle));
    }

    points[++ind].position = points[1].position;

    for (auto& point : points) {
        point.color = color;
        point.position += position.to_sf();
    }
}

void fun::rounded_rect_t::draw(sf::RenderTarget& render_target, sf::RenderStates render_states) const {
    if (should_update) {
        build();

        should_update = false;
    }

    render_target.draw(&points[0], points.size(), sf::TriangleFan);
}

