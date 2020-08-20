#include "Collider.h"

bool Collider::PointVsCircle(const sf::Vector2f& p, const Circle& c) {
    return Math::Scalar(p, c.center) <= c.radius;
}

bool Collider::CircleVsCircle(const Circle& c1, const Circle& c2) {
    return true;//Math::Distance(c1.center, c2.center) <= c1.radius + c2.radius;
}

bool Collider::PointVsRect(const sf::Vector2f& p, const Rect& r) {
    return p <= r.center + r.size / 2.f && p >= r.center - r.size / 2.f ;
}