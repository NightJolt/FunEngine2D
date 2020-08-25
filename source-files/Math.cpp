#include "Math.h"

#include <cmath>

int Math::Random(int a, int b) {
    return rand() % (b - a) + a;
}

float Math::Random(float, float) {
    return 0;
}

bool Math::RandPerc(const int& chance) {
    return Random(1, 100) <= chance;
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
    return window.mapPixelToCoords(p);// * sf::Vector2f(1, -1);
    /*sf::View view = window.getView();

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

    return world_point;*/
}

// Todo not tested yet

sf::Vector2i Math::WorldToScreen(const sf::Vector2f& p, const sf::RenderWindow& window) {
    return window.mapCoordsToPixel(p/* * sf::Vector2f(1, -1)*/);
}

sf::Vector2i Math::WorldToGrid(const sf::Vector2f& p) {
    return sf::Vector2i(std::floor(p.x / TILE_SIZE), std::floor(p.y / TILE_SIZE));
}

sf::Vector2f Math::GridToWorld(const sf::Vector2i& p) {
    return sf::Vector2f(p.x, p.y) * TILE_SIZE;
}

sf::Vector2i Math::GridToChunk(const sf::Vector2i& p) {
    sf::Vector2i chunk_point = sf::Vector2i(p.x / CHUNK_SIZE, p.y / CHUNK_SIZE);

    chunk_point.x -= p.x < 0 && abs(p.x) % CHUNK_SIZE > 0 ? 1 : 0;
    chunk_point.y -= p.y < 0 && abs(p.y) % CHUNK_SIZE > 0 ? 1 : 0;

    return chunk_point;
}

sf::Vector2i Math::GridToTile(const sf::Vector2i& p) {
    return sf::Vector2i(Math::Mod(p.x, CHUNK_SIZE), Math::Mod(p.y, CHUNK_SIZE));
}



sf::Vector2f Math::GravitationalAcceleration(sf::Vector2f p1, sf::Vector2f p2, float m2) {
    sf::Vector2f segment = p2 - p1;

    return Normalize(segment) * m2 / Scalar(segment, segment);
}

sf::Vector2f Math::GravitationalPull(sf::Vector2f p1, float m1, sf::Vector2f p2, float m2) {
    return GravitationalAcceleration(p1, p2, m2) * m1;
}
