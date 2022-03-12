#include "_Math.h"

static std::random_device _random_device_;
static std::mt19937 _engine32_(_random_device_());
static std::mt19937_64 _engine64_(_random_device_());
static std::uniform_int_distribution <int32_t> _uniform_int32_distribution_;
static std::uniform_int_distribution <int64_t> _uniform_int64_distribution_;
static std::uniform_real_distribution <float> _uniform_float_distribution_;

int32_t fun::math::random_32(int32_t a, int32_t b) {
    return _uniform_int32_distribution_(_engine32_, std::uniform_int <int32_t> :: param_type(a, b));
}

int64_t fun::math::random_64(int64_t a, int64_t b) {
    return _uniform_int64_distribution_(_engine64_, std::uniform_int <int64_t> :: param_type(a, b));
}

float fun::math::random_f(float a, float b) {
    return _uniform_float_distribution_(_engine32_, std::uniform_real <float> :: param_type(a, b));
}

bool fun::math::random_chance(float chance) {
    return random_f(0, 100) <= chance;
}

int32_t fun::math::mod(int32_t a, int32_t m) {
    const int32_t r = a % m;

    return r >= 0 ? r : m - r;
}

float fun::math::map_value(float n, float a, float b, float c, float d) {
    return (d - c) / (b - a) * (n - a) + c;
}

fun::vec2f_t fun::math::normalize(const vec2f_t& v) {
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
    return degrees * 0.0174532f;
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

fun::vec2f_t fun::math::gravitational_acceleration(vec2f_t p1, vec2f_t p2, float m2) {
    fun::vec2f_t segment = p2 - p1;

    return normalize(segment) * m2 / scalar(segment, segment);
}

fun::vec2f_t fun::math::gravitational_pull(vec2f_t p1, float m1, vec2f_t p2, float m2) {
    return gravitational_acceleration(p1, p2, m2) * m1;
}
