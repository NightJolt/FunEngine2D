#pragma once

#include "Globals.h"

namespace fun::math {
    namespace constants {
        const constexpr float e = 2.71828182846f;

        const constexpr float pi = 3.14159265359f;
        const constexpr float half_pi = pi * .5f;
        const constexpr float double_pi = pi * 2.f;
        
        const constexpr float sqrt_2 = 1.41421356237f;
        const constexpr float half_sqrt_2 = sqrt_2 * .5f;
        const constexpr float inv_sqrt_2 = half_sqrt_2;

        const constexpr float sqrt_3 = 1.73205080757f;
    }

    int32_t random_32(int32_t, int32_t);
    int64_t random_64(int64_t, int64_t);
    float random_f(float, float);
    bool random_chance(float);

    int mod(int, int);
    float map_value(float, float, float, float, float);
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
    T min(const sf::Vector2 <T>& a) {
        return a.x < a.y ? a.x : a.y;
    }

    template <class T>
    T max(const sf::Vector2 <T>& a) {
        return a.x > a.y ? a.x : a.y;
    }

    template <class T>
    T scalar(const sf::Vector2 <T>& a, const sf::Vector2 <T>& b) {
        return a.x * b.x + a.y * b.y;
    }

    template <class T>
    float manhattan(const sf::Vector2 <T>& v) {
        const auto abs_v = abs(v);

        return abs_v.x + abs_v.y;
    }

    template <class T>
    float magnitude(const sf::Vector2 <T>& v) {
        return sqrt(scalar(v, v));
    }

    template <class T>
    float distance(const sf::Vector2 <T>& a, const sf::Vector2 <T>& b) {
        return magnitude(b - a);
    }

    template <class T>
    sf::Vector2f direction(const sf::Vector2 <T>& a, const sf::Vector2 <T>& b) {
        return normalize((sf::Vector2f)(b - a));
    }

    template <class T>
    T lerp(T a, T b, float v) {
        return a + (b - a) * v;
    }

    template <class T>
    sf::Vector2 <T> lerp(const sf::Vector2 <T>& a, const sf::Vector2 <T>& b, float v) {
        return sf::Vector2 <T> (lerp(a.x, b.x, v), lerp(a.y, b.y, v));
    }

    template <class T>
    sf::Vector2 <T> sqrt(const sf::Vector2 <T>& a) {
        return sf::Vector2 <T> (sqrt(a.x), sqrt(a.y));
    }

    template <class T>
    sf::Vector2 <T> swap(const sf::Vector2 <T>& a) {
        return sf::Vector2 <T> (a.y, a.x);
    }

    template <class T>
    sf::Vector2 <T> abs(const sf::Vector2 <T>& a) {
        return sf::Vector2 <T> (std::abs(a.x), std::abs(a.y));
    }

    template <class T>
    T clamp(T v, T a, T b) {
        return v < a ? a : v > b ? b : v;
    }

    template <class T>
    bool in_bounds(T a, const sf::Vector2<T>& b) {
        return a >= b.x && a <= b.y;
    }
}