#pragma once

#include <SFML/Graphics.hpp>

#pragma region stdlibs

#include <memory>
#include <cstring>
#include <map>
#include <cmath>

#pragma endregion

#pragma region window

#define INIT_SCREEN_SIZE sf::Vector2i(1920, 1440)
#define INIT_VIEW_SIZE sf::Vector2f(1920, 1440)
#define INIT_VIEW_ORIGIN Vector2f(0, 0)

#pragma endregion

#pragma region tilemap

#define CHUNK_SIZE 16
#define TILE_SIZE 8.f
#define TILE_TEXTURE_SIZE 8
#define TILE_ATLAS_SIZE 256
#define RAND_TEXTURE_COUNT 2

#pragma endregion


struct UniqueKey {
    UniqueKey(void* p, const char* k) : ptr(p), key(strdup(k)) {}
    ~UniqueKey() { free(key); }

    bool operator <(const UniqueKey& other) const {
        return strcmp(key, other.key) < 0;
    }

    UniqueKey(const UniqueKey& other) {
        ptr = other.ptr;
        key = strdup(other.key);
    }

    UniqueKey& operator =(const UniqueKey& other) {
        if (&other == this) return *this;

        ptr = other.ptr;
        key = strdup(other.key);

        return *this;
    }

    UniqueKey(UniqueKey&& other) noexcept {
        ptr = other.ptr;
        key = other.key;

        other.ptr = nullptr;
        other.key = nullptr;
    }

    void* ptr;
    char* key;
};



template <typename T>
std::string to_string_key(const sf::Vector2<T>& a) {
    return std::to_string(a.x) + ' ' + std::to_string(a.y);
}

template <typename T>
std::string to_string(const sf::Vector2<T>& a) {
    return "Vector2(" + std::to_string(a.x) + ", " + std::to_string(a.y) + ")";
}

template <typename T>
std::ostream& operator <<(std::ostream& out, const sf::Vector2<T>& a) {
    return out << to_string(a);
}

template <typename T>
sf::Vector2<T> operator *(const sf::Vector2<T>& a, const sf::Vector2<T>& b) {
    return sf::Vector2<T>(a.x * b.x, a.y * b.y);
}

template <typename T>
void operator *=(sf::Vector2<T>& a, const sf::Vector2<T>& b) {
    a = a * b;
}

template <typename T>
sf::Vector2<T> operator /(const sf::Vector2<T>& a, const sf::Vector2<T>& b) {
    return sf::Vector2<T>(a.x / b.x, a.y / b.y);
}

template <typename T>
void operator /=(sf::Vector2<T>& a, const sf::Vector2<T>& b) {
    a = a / b;
}

template <typename T>
sf::Vector2<T> operator +(const sf::Vector2<T>& a, const T& b) {
    return sf::Vector2<T>(a.x + b, a.y + b);
}

template <typename T>
void operator +=(sf::Vector2<T>& a, const T& b) {
    a = a + b;
}

template <typename T>
sf::Vector2<T> operator -(const sf::Vector2<T>& a, const T& b) {
    return sf::Vector2<T>(a.x - b, a.y - b);
}

template <typename T>
void operator -=(sf::Vector2<T>& a, const T& b) {
    a = a - b;
}

template <typename T>
bool operator <(const sf::Vector2<T>& a, const sf::Vector2<T>& b) {
    return a.x < b.x && a.y < b.y;
}

template <typename T>
bool operator <=(const sf::Vector2<T>& a, const sf::Vector2<T>& b) {
    return a.x <= b.x && a.y <= b.y;
}

template <typename T>
bool operator >(const sf::Vector2<T>& a, const sf::Vector2<T>& b) {
    return b < a;
}

template <typename T>
bool operator >=(const sf::Vector2<T>& a, const sf::Vector2<T>& b) {
    return b <= a;
}