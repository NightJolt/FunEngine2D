#include "render/shapes/curved_line.h"

fun::curved_line_t::curved_line_t() {
    build();
}

void fun::curved_line_t::set_points(vec2f_t f, vec2f_t t) {
    if (from == f && to == t) return;

    from = f;
    to = t;

    should_update = true;
}

void fun::curved_line_t::set_radius(float r) {
    if (radius != r) return;

    radius = r;

    should_update = true;
}

void fun::curved_line_t::set_smoothness(int s) {
    if (smoothness != s) return;

    smoothness = s;

    should_update = true;
}

void fun::curved_line_t::curve_at(float c) {
    if (curving_point != c) return;

    curving_point = c;

    should_update = true;
}

void fun::curved_line_t::set_color(sf::Color c) {
    if (color == c) return;

    color = c;

    for (auto& point : points) {
        point.color = color;
    }
}

void fun::curved_line_t::build() const {
    if (std::abs(to.x - from.x) < 2 * radius || std::abs(to.y - from.y) < 2 * radius) {
        points.resize(2);

        points[0].position = from.to_sf();
        points[1].position = to.to_sf();
    } else {
        points.resize(8 + 4 * smoothness);

        float mid_x = from.x + (to.x - from.x - radius * 2.f) * curving_point + radius;
        float step = radius / (float)(smoothness + 1);
        int ind = -1;
        float inv_x = from.x < to.x ? 1 : -1;
        float inv_y = from.y > to.y ? 1 : -1;
        vec2f_t round_pnt_from = vec2f_t(mid_x, from.y) - vec2f_t(inv_x, inv_y) * radius;
        vec2f_t round_pnt_to = vec2f_t(mid_x, to.y) + vec2f_t(inv_x, inv_y) * radius;

        points[++ind].position = from.to_sf();
        points[++ind].position = sf::Vector2f(mid_x - radius * inv_x, from.y);

        for (int i = 1; i <= smoothness; i++) {
            points[++ind].position = (round_pnt_from + math::normalize(vec2f_t(mid_x - (radius - step * (float)i) * inv_x, from.y) - round_pnt_from) * radius).to_sf();
        }

        points[++ind].position = (round_pnt_from + math::normalize(vec2f_t(mid_x, from.y) - round_pnt_from) * radius).to_sf();

        for (int i = 1; i <= smoothness; i++) {
            points[++ind].position = (round_pnt_from + math::normalize(vec2f_t(mid_x, from.y - step * (float)i * inv_y) - round_pnt_from) * radius).to_sf();
        }

        points[++ind].position = sf::Vector2f(mid_x, from.y - radius * inv_y);
        points[++ind].position = sf::Vector2f(mid_x, to.y + radius * inv_y);

        for (int i = smoothness; i >= 1; i--) {
            points[++ind].position = (round_pnt_to + math::normalize(vec2f_t(mid_x, to.y + step * (float)i * (from.y > to.y ? 1.f : -1.f)) - round_pnt_to) * radius).to_sf();
        }

        points[++ind].position = (round_pnt_to + math::normalize(vec2f_t(mid_x, to.y) - round_pnt_to) * radius).to_sf();

        for (int i = 1; i <= smoothness; i++) {
            points[++ind].position = (round_pnt_to + math::normalize(vec2f_t(mid_x + step * (float)i * (from.x < to.x ? 1.f : -1.f), to.y) - round_pnt_to) * radius).to_sf();
        }

        points[++ind].position = sf::Vector2f(mid_x + radius * inv_x, to.y);
        points[++ind].position = to.to_sf();
    }

    for (auto& point : points) {
        point.color = color;
    }
}

void fun::curved_line_t::draw(sf::RenderTarget& render_target, sf::RenderStates rs) const {
    if (should_update) {
        build();

        should_update = false;
    }

    render_target.draw(&points[0], points.size(), sf::LineStrip);
}