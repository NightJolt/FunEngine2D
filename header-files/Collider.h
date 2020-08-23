#pragma once

#include <SFML/Graphics.hpp>

#include "Math.h"

/*
 * - Not implemented
 * + Implemented
 * * In process
 * / N/A or already defined
 *          Point    Line     Ray    Circle    Rect
 * Point      /       -        -       +        +
 * Line       /       -        -       -        +
 * Ray        /       /        -       -        +
 * Circle     /       /        /       +        -
 * Rect       /       /        /       /        +
 */

class Collider {
public:
    struct Line {
        explicit Line (sf::Vector2f s = sf::Vector2f(0, 0), sf::Vector2f e = sf::Vector2f(0, 0)) : start(s), end(e) {}

        sf::Vector2f start;
        sf::Vector2f end;
    };

    struct Ray {
        explicit Ray (sf::Vector2f s = sf::Vector2f(0, 0), sf::Vector2f d = sf::Vector2f(0, 0)) : start(s), dir(d) {}

        sf::Vector2f start;
        sf::Vector2f dir;
    };

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
    static bool RectVsRect(const Rect&, const Rect&);
    static bool LineVsRect(const Line&, const Rect&, float* = nullptr, float* = nullptr);
    static bool RayVsRect(const Ray&, const Rect&, float* = nullptr, float* = nullptr);

private:
    static bool LinearVsRect(const Line&, const Rect&, float&, float&);
};