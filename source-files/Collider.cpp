#include "Collider.h"

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

bool Collider::LinearVsRect(const Collider::Line& line, const Collider::Rect& rect, float& t1, float& t2) {
    sf::Vector2f dir = line.end - line.start;

    sf::Vector2f t_n = (rect.center - rect.size * .5f - line.start) / dir;
    sf::Vector2f t_f = (rect.center + rect.size * .5f - line.start) / dir;

    if (t_n.x > t_f.x) std::swap(t_n.x, t_f.x);
    if (t_n.y > t_f.y) std::swap(t_n.y, t_f.y);

    t1 = Math::Max(t_n);
    t2 = Math::Min(t_f);

    return t_n.x < t_f.y && t_n.y < t_f.x;
}

bool Collider::LineVsRect(const Collider::Line& line, const Collider::Rect& rect, float* t_n, float* t_f) {
    bool d_t_n = t_n, d_t_f = t_f;

    if (!d_t_n) t_n = new float;
    if (!d_t_f) t_f = new float;

    if (!LinearVsRect(line, rect, *t_n, *t_f)) return false;

    bool result = (*t_n >= 0 && *t_n <= 1) || (*t_f >= 0 && *t_f <= 1);

    if (!d_t_n) delete t_n;
    if (!d_t_f) delete t_f;

    return result;
}


bool Collider::RayVsRect(const Collider::Ray& ray, const Collider::Rect& rect, float* t_n, float* t_f) {
    bool d_t_n = t_n, d_t_f = t_f;

    if (!d_t_n) t_n = new float;
    if (!d_t_f) t_f = new float;

    if (!LinearVsRect(Collider::Line(ray.start, ray.start + ray.dir), rect, *t_n, *t_f)) return false;

    bool result = *t_n >= 0 || *t_f >= 0;

    if (!d_t_n) delete t_n;
    if (!d_t_f) delete t_f;

    return result;
}