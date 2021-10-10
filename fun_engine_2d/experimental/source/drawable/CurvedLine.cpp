#include "drawable/CurvedLine.h"

fun::CurvedLine::CurvedLine() {
    SetColor(sf::Color(150, 150, 150));

    Build();
}

void fun::CurvedLine::SetPoints(sf::Vector2f f, sf::Vector2f t, bool should_update) {
    from = f;
    to = t;

    if (should_update) Build();
}

void fun::CurvedLine::SetRadius(float r, bool should_update) {
    radius = r;

    if (should_update) Build();
}

void fun::CurvedLine::SetSmoothness(int s, bool should_update) {
    smoothness = s;

    if (should_update) Build();
}

void fun::CurvedLine::CurveAt(float c, bool should_update) {
    curving_point = c;

    if (should_update) Build();
}

void fun::CurvedLine::SetColor(sf::Color c, bool should_update) {
    color = c;

    if (should_update) {
        for (auto& point : points) {
            point.color = color;
        }
    }
}

void fun::CurvedLine::Build() {
    if (std::abs(to.x - from.x) < 2 * radius || std::abs(to.y - from.y) < 2 * radius) {
        points.resize(2);

        points[0].position = from;
        points[1].position = to;
    } else {
        points.resize(8 + 4 * smoothness);

        float mid_x = from.x + (to.x - from.x - radius * 2.f) * curving_point + radius;
        float step = radius / (float)(smoothness + 1);
        int ind = -1;
        float inv_x = from.x < to.x ? 1 : -1;
        float inv_y = from.y > to.y ? 1 : -1;
        sf::Vector2f round_pnt_from = sf::Vector2f(mid_x, from.y) - radius * sf::Vector2f(inv_x, inv_y);
        sf::Vector2f round_pnt_to = sf::Vector2f(mid_x, to.y) + radius * sf::Vector2f(inv_x, inv_y);

        points[++ind].position = from;
        points[++ind].position = sf::Vector2f(mid_x - radius * inv_x, from.y);

        for (int i = 1; i <= smoothness; i++) {
            points[++ind].position = round_pnt_from + fun::Math::Normalize(sf::Vector2f(mid_x - (radius - step * (float)i) * inv_x, from.y) - round_pnt_from) * radius;
        }

        points[++ind].position = round_pnt_from + fun::Math::Normalize(sf::Vector2f(mid_x, from.y) - round_pnt_from) * radius;

        for (int i = 1; i <= smoothness; i++) {
            points[++ind].position = round_pnt_from + fun::Math::Normalize(sf::Vector2f(mid_x, from.y - step * (float)i * inv_y) - round_pnt_from) * radius;
        }

        points[++ind].position = sf::Vector2f(mid_x, from.y - radius * inv_y);
        points[++ind].position = sf::Vector2f(mid_x, to.y + radius * inv_y);

        for (int i = smoothness; i >= 1; i--) {
            points[++ind].position = round_pnt_to + fun::Math::Normalize(sf::Vector2f(mid_x, to.y + step * (float)i * (from.y > to.y ? 1.f : -1.f)) - round_pnt_to) * radius;
        }

        points[++ind].position = round_pnt_to + fun::Math::Normalize(sf::Vector2f(mid_x, to.y) - round_pnt_to) * radius;

        for (int i = 1; i <= smoothness; i++) {
            points[++ind].position = round_pnt_to + fun::Math::Normalize(sf::Vector2f(mid_x + step * (float)i * (from.x < to.x ? 1.f : -1.f), to.y) - round_pnt_to) * radius;
        }

        points[++ind].position = sf::Vector2f(mid_x + radius * inv_x, to.y);
        points[++ind].position = to;
    }

    for (auto& point : points) {
        point.color = color;
    }
}

void fun::CurvedLine::draw(sf::RenderTarget& rt, sf::RenderStates rs) const {
    rt.draw(&points[0], points.size(), sf::LineStrip);
}