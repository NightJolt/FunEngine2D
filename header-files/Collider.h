#pragma once

#include <SFML/Graphics.hpp>

#include "Math.h"

/*
 * S - Static collision
 * D - Dynamic collision
 * (S/D)
 * - Not implemented
 * + Implemented
 * ^ In process
 * # N/A or already defined
 *          Point    Line     Ray    Circle    Rect
 * Point     -/-     -/-      -/-     +/-      +/-
 * Line       #      +/-      -/-     -/-      +/-
 * Ray        #       #       -/-     -/-      +/-
 * Circle     #       #        #      +/-      -/-
 * Rect       #       #        #       #       +/+
 */

class Collider {
public:
    static const sf::Vector2f ContactDirVal[];
    enum ContactDir { Up, Right, Down, Left, Center };
    static ContactDir GetContactDir(sf::Vector2f, sf::Vector2f); // Not supported diagonal directions as they have practically zero chance to occur

    struct Collision {
        Collision() : result(false), near_t(0), far_t(0), near_p(sf::Vector2f(0, 0)), far_p(sf::Vector2f(0, 0)), near_contact_direction(ContactDir::Center), far_contact_direction(ContactDir::Center) {}
        ~Collision() = default;

        explicit operator bool() const {
            return result;
        }

        bool result;

        float near_t, far_t;
        sf::Vector2f near_p, far_p;

        ContactDir near_contact_direction;
        ContactDir far_contact_direction;
    };

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
        explicit Circle (sf::Vector2f c = sf::Vector2f(0, 0), float r = 0, sf::Vector2f v = sf::Vector2f(0, 0)) : center(c), radius(r), vel(v) {}

        sf::Vector2f center;
        float radius;
        sf::Vector2f vel;
    };

    struct Rect {
        explicit Rect (sf::Vector2f c = sf::Vector2f(0, 0), sf::Vector2f s = sf::Vector2f(0, 0), sf::Vector2f v = sf::Vector2f(0, 0)) : center(c), size(s), vel(v) {}

        sf::Vector2f center;
        sf::Vector2f size;
        sf::Vector2f vel;
    };

    static bool PointVsCircle(const sf::Vector2f&, const Circle&);
    static bool CircleVsCircle(const Circle&, const Circle&);
    static bool PointVsRect(const sf::Vector2f&, const Rect&);
    static bool RectVsRect(const Rect&, const Rect&);
    static Collision LineVsLine(const Line&, const Line&);
    static Collision LineVsRect(const Line&, const Rect&);
    static Collision RayVsRect(const Ray&, const Rect&);

    static Collision DynamicRectVsRect(const Rect&, const Rect&);

private:
    static Collision LinearVsRect(const Line&, const Rect&);
};