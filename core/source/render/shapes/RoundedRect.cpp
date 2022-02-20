#include "render/shapes/RoundedRect.h"

fun::RoundedRect::RoundedRect() {
    Build();
}

void fun::RoundedRect::SetRadius(float r) {
    if (radius == r) return;

    radius = r;

    should_update = true;
}

void fun::RoundedRect::SetPosition(const sf::Vector2f& p) {
    if (position == p) return;

    auto delta = p - position;

    for (auto& point : points) {
        point.position += delta;
    }

    position = p;
}

const sf::Vector2f& fun::RoundedRect::GetPosition() const {
    return position;
}

void fun::RoundedRect::SetSize(const sf::Vector2f& s) {
    if (size == s) return;

    size = s;

    should_update = true;
}

const sf::Vector2f& fun::RoundedRect::GetSize() const {
    return size;
}

void fun::RoundedRect::SetSmoothness(int s) {
    if (smoothness == s) return;

    smoothness = s;

    should_update = true;
}

void fun::RoundedRect::SetFillColor(const sf::Color& c) {
    if (color == c) return;

    color = c;

    should_update = true;
}

void fun::RoundedRect::Build() const {
    points.resize(10 + 4 * smoothness);

    points[0].position = { 0, 0 };

    int ind = 0;
    const sf::Vector2f half_size = size * .5f;
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
        point.position += position;
    }
}

void fun::RoundedRect::draw(sf::RenderTarget& render_target, sf::RenderStates render_states) const {
    if (should_update) {
        Build();

        should_update = false;
    }

    render_target.draw(&points[0], points.size(), sf::TriangleFan);
}

