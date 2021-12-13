#include "_Math.h"

int fun::math::random(int a, int b) {
    return rand() % (b - a) + a;
}

float fun::math::random(float a, float b) {
    return random((int)a, (int)b);
}

bool fun::math::random_chance(const int& chance) {
    return random(1, 100) <= chance;
}

int fun::math::mod(const int& a, const int& m) {
    const int r = a % m;

    return r >= 0 ? r : m - r;
}

float fun::math::map_value(const float& n, const float& a, const float& b, const float& c, const float& d) {
    return (d - c) / (b - a) * (n - a) + c;
}

sf::Vector2f fun::math::normalize(const sf::Vector2f& v) {
    const float l = magnitude(v);

    return l ? v / l : v;
}

float fun::math::q_rsqrt(float v) {
    float y = v;
    long i = 0x5f3759df - ((*(long*)&y) >> 1);

    y = *(float*)&i;

    return y * (1.5f - (y * y * v * .5f));
}

float fun::math::radians(float degrees) {
    return degrees * 0.017435f;
}

float fun::math::degrees(float radians) {
    return radians * 57.295779f;
}

// todo make grid constants local
// sf::Vector2i fun::math::WorldToGrid(const sf::Vector2f& p) {
//     return sf::Vector2i(std::floor(p.x / TILE_SIZE), std::floor(p.y / TILE_SIZE));
// }

// sf::Vector2f fun::math::GridToWorld(const sf::Vector2i& p) {
//     return sf::Vector2f(p.x, p.y) * TILE_SIZE;
// }

// sf::Vector2i fun::math::GridToChunk(const sf::Vector2i& p) {
//     sf::Vector2i chunk_point = sf::Vector2i(p.x / CHUNK_SIZE, p.y / CHUNK_SIZE);

//     chunk_point.x -= p.x < 0 && abs(p.x) % CHUNK_SIZE > 0 ? 1 : 0;
//     chunk_point.y -= p.y < 0 && abs(p.y) % CHUNK_SIZE > 0 ? 1 : 0;

//     return chunk_point;
// }

// sf::Vector2i fun::math::GridToTile(const sf::Vector2i& p) {
//     return sf::Vector2i(Math::Mod(p.x, CHUNK_SIZE), Math::Mod(p.y, CHUNK_SIZE));
// }

sf::Vector2f fun::math::gravitational_acceleration(sf::Vector2f p1, sf::Vector2f p2, float m2) {
    sf::Vector2f segment = p2 - p1;

    return normalize(segment) * m2 / scalar(segment, segment);
}

sf::Vector2f fun::math::gravitational_pull(sf::Vector2f p1, float m1, sf::Vector2f p2, float m2) {
    return gravitational_acceleration(p1, p2, m2) * m1;
}
