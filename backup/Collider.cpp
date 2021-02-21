#include "Collider.h"

const sf::Vector2f Collider::ContactDirVal[] = {
        sf::Vector2f(0, -1),
        sf::Vector2f(1, 0),
        sf::Vector2f(0, 1),
        sf::Vector2f(-1, 0),
        sf::Vector2f(0, 0),
};

Collider::ContactDir Collider::GetContactDir(sf::Vector2f t, sf::Vector2f d) {
    return t.x > t.y ? d.x < 0 ? ContactDir::Right : ContactDir::Left : d.y < 0 ? ContactDir::Up : ContactDir::Down;
}

bool Collider::PointVsCircle(const sf::Vector2f& p, const Circle& c) {
    return Math::Distance(sf::Vector2f(1, 1), sf::Vector2f(2, 2)) <= c.radius;
}

bool Collider::CircleVsCircle(const Circle& c1, const Circle& c2) {
    return Math::Distance(c1.center, c2.center) <= c1.radius + c2.radius;
}

bool Collider::PointVsRect(const sf::Vector2f& p, const Rect& r) {
    return p <= r.center + r.size * .5f && p >= r.center - r.size * .5f;
}

bool Collider::RectVsRect(const Rect& r1, const Rect& r2) {
    return (r1.center - r1.size * .5f) < (r2.center + r2.size * .5f) && (r1.center + r1.size * .5f) > (r2.center - r2.size * .5f);
}

Collider::Collision Collider::LinearVsRect(const Collider::Line& line, const Collider::Rect& rect) {
    Collision collision;//(t_n.x < t_f.y && t_n.y < t_f.x, Math::Max(t_n), Math::Min(t_f));

    sf::Vector2f directed_segment = line.end - line.start;

    sf::Vector2f t_n = (rect.center - rect.size * .5f - line.start) / directed_segment;
    sf::Vector2f t_f = (rect.center + rect.size * .5f - line.start) / directed_segment;

    if (t_n.x > t_f.x) std::swap(t_n.x, t_f.x);
    if (t_n.y > t_f.y) std::swap(t_n.y, t_f.y);

    collision.result = t_n.x < t_f.y && t_n.y < t_f.x;
    collision.near_t = Math::Max(t_n);
    collision.far_t = Math::Min(t_f);
    collision.near_p = Math::Lerp(line.start, line.end, collision.near_t);
    collision.far_p = Math::Lerp(line.start, line.end, collision.far_t);
    collision.near_contact_direction = GetContactDir(t_n, directed_segment);
    collision.near_contact_direction = GetContactDir(t_f, directed_segment);


    return collision;
}

Collider::Collision Collider::LineVsRect(const Collider::Line& line, const Collider::Rect& rect) {
    Collision linear_collision = LinearVsRect(line, rect);
    sf::Vector2f bounds(0, 1);

    linear_collision.result = linear_collision && (Math::InBounds(linear_collision.near_t, bounds) || Math::InBounds(linear_collision.far_t, bounds));

    return linear_collision;
}


Collider::Collision Collider::RayVsRect(const Collider::Ray& ray, const Collider::Rect& rect) {
    Collision linear_collision = LinearVsRect(Collider::Line(ray.start, ray.start + ray.dir), rect);

    linear_collision.result = linear_collision && (linear_collision.near_t >= 0 || linear_collision.far_t >= 0);

    return linear_collision;
}

Collider::Collision Collider::DynamicRectVsRect(const Collider::Rect& r1, const Collider::Rect& r2) {
    Collision dynamic_collision;

    if (!r1.vel.x && !r1.vel.y) return dynamic_collision;

    Rect expanded_r2 = r2;
    expanded_r2.size += r1.size;

    dynamic_collision = LineVsRect(Line(r1.center, r1.vel), expanded_r2);

    return dynamic_collision;
}

Collider::Collision Collider::LineVsLine(const Collider::Line& a, const Collider::Line& b) {
    Collision collision;

    float x1_x3 = a.start.x - b.start.x;
    float y3_y4 = b.start.y - b.end.y;
    float y1_y3 = a.start.y - b.start.y;
    float x3_x4 = b.start.x - b.end.x;
    float x1_x2 = a.start.x - a.end.x;
    float y1_y2 = a.start.y - a.end.y;

    float denominator = x1_x2 * y3_y4 - y1_y2 * x3_x4;

    if (denominator == 0) return collision;

    collision.near_t = (x1_x3 * y3_y4 - y1_y3 * x3_x4) / denominator;
    collision.far_t = -(x1_x2 * y1_y3 - y1_y2 * x1_x3) / denominator;

    collision.result = 0 <= collision.near_t && collision.near_t <= 1 && 0 <= collision.far_t && collision.far_t <= 1;

    return collision;
}