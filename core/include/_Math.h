#pragma once

#include "Globals.h"

namespace fun::math {
    int random(int, int); // TODO change to C++11 random
    float random(float, float);
    bool random_chance(const int&);
    int mod(const int&, const int&);
    float map_value(const float&, const float&, const float&, const float&, const float&);
    sf::Vector2f normalize(const sf::Vector2f&);
    float q_rsqrt(float);
    float radians(float);
    float degrees(float);

    // sf::Vector2f ScaleViewWithWindow();
    // sf::Vector2i WorldToGrid(const sf::Vector2f&);
    // sf::Vector2f GridToWorld(const sf::Vector2i&);
    // sf::Vector2i GridToChunk(const sf::Vector2i&);
    // sf::Vector2i GridToTile(const sf::Vector2i&);

    // todo: move to physics
    sf::Vector2f gravitational_acceleration(sf::Vector2f, sf::Vector2f, float);
    sf::Vector2f gravitational_pull(sf::Vector2f, float, sf::Vector2f, float);

    template <class T>
    T min(const sf::Vector2<T>& a) {
        return a.x < a.y ? a.x : a.y;
    }

    template <class T>
    T max(const sf::Vector2<T>& a) {
        return a.x > a.y ? a.x : a.y;
    }

    template <class T>
    T scalar(const sf::Vector2<T>& a, const sf::Vector2<T>& b) {
        return a.x * b.x + a.y * b.y;
    }

    template <class T>
    float manhattan(const sf::Vector2<T>& v) {
        const auto abs_v = abs(v);

        return abs_v.x + abs_v.y;
    }

    template <class T>
    float magnitude(const sf::Vector2<T>& v) {
        return sqrt(scalar(v, v));
    }

    template <class T>
    float distance(const sf::Vector2<T>& a, const sf::Vector2<T>& b) {
        return magnitude(b - a);
    }

    template <class T>
    sf::Vector2f direction(const sf::Vector2<T>& a, const sf::Vector2<T>& b) {
        return normalize((sf::Vector2f)(b - a));
    }

    template <class T>
    T lerp(const T& a, const T& b, const float& v) {
        return a + (b - a) * v;
    }

    template <class T>
    sf::Vector2<T> lerp(const sf::Vector2<T>& a, const sf::Vector2<T>& b, const float& v) {
        return sf::Vector2<T>(Lerp(a.x, b.x, v), Lerp(a.y, b.y, v));
    }

    template <class T>
    sf::Vector2<T> sqrt(const sf::Vector2<T>& a) {
        return sf::Vector2<T>(sqrt(a.x), sqrt(a.y));
    }

    template <class T>
    sf::Vector2<T> swap(const sf::Vector2<T>& a) {
        return sf::Vector2<T>(a.y, a.x);
    }

    template <class T>
    sf::Vector2<T> abs(const sf::Vector2<T>& a) {
        return sf::Vector2<T>(std::abs(a.x), std::abs(a.y));
    }

    template <class T>
    T clamp(const T& v, const T& a, const float& b) {
        return v < a ? a : v > b ? b : v;
    }

    template <class T>
    bool in_bounds(const T& a, const sf::Vector2<T>& b) {
        return a >= b.x && a <= b.y;
    }
}