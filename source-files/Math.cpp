#include "Math.h"

bool Math::RandPerc(const int& chance) {
    return rand() % 100 + 1 <= chance;
}

int Math::Mod(const int& a, const unsigned int& m) {
    const int r = a % m;

    return r >= 0 ? r : m - r;
}

float Math::MapValue(const float& n, const float& a, const float& b, const float& c, const float& d) {
    return (d - c) / (b - a) * (n - a) + c;
}

sf::Vector2f Math::Normalize(const sf::Vector2f& v) {
    const float l = Magnitude(v);

    return l ? v / l : v;
}

template<class T>
float Math::Scalar(const sf::Vector2<T>& a, const sf::Vector2<T>& b) {
    return a.x * b.x + a.y * b.y;
}

template<class T>
float Math::Magnitude(const sf::Vector2<T>& v) {
    return sqrt(Scalar(v, v));
}

sf::Vector2i Math::WorldToGrid(const sf::Vector2f& p) {
    return sf::Vector2i();
}

sf::Vector2f Math::GridToWorld(const sf::Vector2i& p) {
    return sf::Vector2f();
}

sf::Vector2i Math::GridToChunk(const sf::Vector2i& p) {
    return sf::Vector2i();
}

sf::Vector2i Math::GridToTile(const sf::Vector2i& p) {
    return sf::Vector2i();
}