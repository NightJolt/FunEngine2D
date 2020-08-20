#pragma once

#include <SFML/Graphics.hpp>

#include "Math.h"

class Collider {
public:
    struct Circle {
        explicit Circle (sf::Vector2f c = sf::Vector2f(0, 0), float r = 0) : center(c), radius(r) {}

        sf::Vector2f center;
        float radius;
    };

    struct Rect {
        explicit Rect (sf::Vector2f c = sf::Vector2f(0, 0), sf::Vector2f s = sf::Vector2f(0, 0)) : center(c), size(s) {}

        sf::Vector2f center;
        sf::Vector2f size;
    };

    static bool PointVsCircle(const sf::Vector2f&, const Circle&);
    static bool CircleVsCircle(const Circle&, const Circle&);
    static bool PointVsRect(const sf::Vector2f&, const Rect&);
    //static bool RectVsRect(const Circle&, const Rect&);
};