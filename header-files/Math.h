#pragma once

#include "SFML/Graphics.hpp"

#include "globals.h"

#include <cmath>

class Math {
public:
    static bool RandPerc(const int&);
    static int Mod(const int&, const unsigned int&);
    static float MapValue(const float&, const float&, const float&, const float&, const float&);
    static sf::Vector2f Normalize(const sf::Vector2f&);

    static sf::Vector2f ScaleViewWithWindow(); // needs buffer
    static sf::Vector2f ScreenToWorld(sf::Vector2i, const sf::RenderWindow&);
    static sf::Vector2i WorldToScreen(const sf::Vector2f&, const sf::RenderWindow&);
    static sf::Vector2i WorldToGrid(const sf::Vector2f&);
    static sf::Vector2f GridToWorld(const sf::Vector2i&);
    static sf::Vector2i GridToChunk(const sf::Vector2i&);
    static sf::Vector2i GridToTile(const sf::Vector2i&);

    template <class T>
    static T Min(const sf::Vector2<T>& a) {
        return a.x < a.y ? a.x : a.y;
    }

    template <class T>
    static T Max(const sf::Vector2<T>& a) {
        return a.x > a.y ? a.x : a.y;
    }

    template <class T>
    static T Scalar(const sf::Vector2<T>& a, const sf::Vector2<T>& b) {
        return a.x * b.x + a.y * b.y;
    }

    template <class T>
    static float Magnitude(const sf::Vector2<T>& v) {
        return sqrt(Scalar(v, v));
    }

    template <class T>
    static float Distance(const sf::Vector2<T>& a, const sf::Vector2<T>& b) {
        return Magnitude(b - a);
    }

    template <class T>
    static sf::Vector2f Direction(const sf::Vector2<T>& a, const sf::Vector2<T>& b) {
        return Normalize((sf::Vector2f)(b - a));
    }

    template <class T>
    static T Lerp(const T& a, const T& b, const float& v) {
        return a + (b - a) * v;
    }

    template <class T>
    static sf::Vector2<T> Lerp(const sf::Vector2<T>& a, const sf::Vector2<T>& b, const float& v) {
        return Vector2<T>(Lerp(a.x, b.x, v), Lerp(a.y, b.y, v));
    }
};