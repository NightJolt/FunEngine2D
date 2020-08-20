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

sf::Vector2f Math::ScreenToWorld(sf::Vector2i p, const sf::RenderWindow& window) {
    //return window.mapPixelToCoords(p) * sf::Vector2f(1, -1);
    sf::View view = window.getView();

    // set origin to bottom left
    p.y = window.getSize().y - p.y;

    // map from screen to view
    float x = MapValue(p.x, 0, window.getSize().x, 0, view.getSize().x);
    float y = MapValue(p.y, 0, window.getSize().y, 0, view.getSize().y);

    // center coordinates
    sf::Vector2f world_point = sf::Vector2f(x, y) - view.getSize() * .5f;

    // apply camera position
    world_point.x += view.getCenter().x;
    world_point.y -= view.getCenter().y;

    return world_point;
}

sf::Vector2i Math::WorldToScreen(const sf::Vector2f& p, const sf::RenderWindow& window) {
    return window.mapCoordsToPixel(p * sf::Vector2f(1, -1));
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

template<class T>
float Math::Scalar(const sf::Vector2<T>& a, const sf::Vector2<T>& b) {
    return a.x * b.x + a.y * b.y;
}

template<class T>
float Math::Magnitude(const sf::Vector2<T>& v) {
    return sqrt(Scalar(v, v));
}

template<class T>
float Math::Distance(const sf::Vector2<T>& a, const sf::Vector2<T>& b) {
    return a.x * b.x + a.y * b.y;
}

template<class T>
float Math::Direction(const sf::Vector2<T>& a, const sf::Vector2<T>& b) {
    return Normalize(b - a);
}

template<class T>
T Math::Lerp(const T& a, const T& b, const float& v) {
    return a + (b - a) * v;
}

template<class T>
sf::Vector2<T> Math::Lerp(const sf::Vector2<T>& a, const sf::Vector2<T>& b, const float& v) {
    return Vector2<T>(Lerp(a.x, b.x, v), Lerp(a.y, b.y, v));
}