#pragma once

#pragma region flags

#define ENABLE_PRINTING

#define USES_SFML
//#define USES_IMGUI
//#define USES_LUA

#if defined(USES_SFML)
#define SFML_VEC2_OVERLOADS
#define SFML_VEC3_OVERLOADS
#endif

#pragma endregion

#pragma region libs

#if defined(USES_SFML)
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#endif

#if defined(USES_IMGUI)
#include <imgui.h>
#include <imgui-SFML.h>
#endif

#pragma endregion

#pragma region stdlibs

#if defined(ENABLE_PRINTING)
#include <iostream>
#endif

#include <memory>
#include <cstring>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <cmath>
#include <vector>
#include <array>
#include <queue>

#pragma endregion

/*#pragma region tilemap

#define CHUNK_SIZE 16
#define TILE_SIZE 8.f
#define TILE_TEXTURE_SIZE 8
#define TILE_ATLAS_SIZE 256
#define RAND_TEXTURE_COUNT 2

#pragma endregion*/

extern sf::RenderWindow* glob_window; // todo: Move to window manager

#define LOCALIZE(type, body) [this]() -> type body

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

#pragma region sfml_vec2
#if defined(SFML_VEC2_OVERLOADS)

template <typename T>
inline std::string to_string_key(const sf::Vector2<T>& a) {
    return std::to_string(a.x) + ' ' + std::to_string(a.y);
}

template <typename T>
inline std::string to_string(const sf::Vector2<T>& a) {
    return "Vector2(" + std::to_string(a.x) + ", " + std::to_string(a.y) + ")";
}

template <typename T>
inline std::ostream& operator <<(std::ostream& out, const sf::Vector2<T>& a) {
    return out << to_string(a);
}

template <typename T>
inline sf::Vector2<T> operator *(const sf::Vector2<T>& a, const sf::Vector2<T>& b) {
    return sf::Vector2<T>(a.x * b.x, a.y * b.y);
}

template <typename T>
inline void operator *=(sf::Vector2<T>& a, const sf::Vector2<T>& b) {
    a = a * b;
}

template <typename T>
inline sf::Vector2<T> operator /(const sf::Vector2<T>& a, const sf::Vector2<T>& b) {
    return sf::Vector2<T>(a.x / b.x, a.y / b.y);
}

template <typename T>
inline void operator /=(sf::Vector2<T>& a, const sf::Vector2<T>& b) {
    a = a / b;
}

template <typename T>
inline sf::Vector2<T> operator +(const sf::Vector2<T>& a, const T& b) {
    return sf::Vector2<T>(a.x + b, a.y + b);
}

template <typename T>
inline void operator +=(sf::Vector2<T>& a, const T& b) {
    a = a + b;
}

template <typename T>
inline sf::Vector2<T> operator -(const sf::Vector2<T>& a, const T& b) {
    return sf::Vector2<T>(a.x - b, a.y - b);
}

template <typename T>
inline void operator -=(sf::Vector2<T>& a, const T& b) {
    a = a - b;
}

template <typename T>
inline bool operator <(const sf::Vector2<T>& a, const sf::Vector2<T>& b) {
    return a.x < b.x && a.y < b.y;
}

template <typename T>
inline bool operator <=(const sf::Vector2<T>& a, const sf::Vector2<T>& b) {
    return a < b || a == b;
}

template <typename T>
inline bool operator >(const sf::Vector2<T>& a, const sf::Vector2<T>& b) {
    return b < a;
}

template <typename T>
inline bool operator >=(const sf::Vector2<T>& a, const sf::Vector2<T>& b) {
    return b <= a;
}

#endif
#pragma endregion

#pragma region sfml_vec3
#if defined(SFML_VEC3_OVERLOADS)

template <typename T>
inline std::string to_string_key(const sf::Vector3<T>& a) {
    return std::to_string(a.x) + ' ' + std::to_string(a.y) + ' ' + std::to_string(a.z);
}

template <typename T>
inline std::string to_string(const sf::Vector3<T>& a) {
    return "Vector3(" + std::to_string(a.x) + ", " + std::to_string(a.y) + ", " + std::to_string(a.z) + ")";
}

template <typename T>
inline std::ostream& operator <<(std::ostream& out, const sf::Vector3<T>& a) {
    return out << to_string(a);
}

template <typename T>
inline sf::Vector3<T> operator *(const sf::Vector3<T>& a, const sf::Vector3<T>& b) {
    return sf::Vector3<T>(a.x * b.x, a.y * b.y, a.z * b.z);
}

template <typename T>
inline void operator *=(sf::Vector3<T>& a, const sf::Vector3<T>& b) {
    a = a * b;
}

template <typename T>
inline sf::Vector3<T> operator /(const sf::Vector3<T>& a, const sf::Vector3<T>& b) {
    return sf::Vector3<T>(a.x / b.x, a.y / b.y, a.z / b.z);
}

template <typename T>
inline void operator /=(sf::Vector3<T>& a, const sf::Vector3<T>& b) {
    a = a / b;
}

template <typename T>
inline sf::Vector3<T> operator +(const sf::Vector3<T>& a, const T& b) {
    return sf::Vector3<T>(a.x + b, a.y + b, a.z + b);
}

template <typename T>
inline void operator +=(sf::Vector3<T>& a, const T& b) {
    a = a + b;
}

template <typename T>
inline sf::Vector3<T> operator -(const sf::Vector3<T>& a, const T& b) {
    return sf::Vector3<T>(a.x - b, a.y - b, a.z - b);
}

template <typename T>
inline void operator -=(sf::Vector3<T>& a, const T& b) {
    a = a - b;
}

template <typename T>
inline bool operator <(const sf::Vector3<T>& a, const sf::Vector3<T>& b) {
    return a.x < b.x && a.y < b.y && a.z < b.z;
}

template <typename T>
inline bool operator <=(const sf::Vector3<T>& a, const sf::Vector3<T>& b) {
    return a < b || a == b;
}

template <typename T>
inline bool operator >(const sf::Vector3<T>& a, const sf::Vector3<T>& b) {
    return b < a;
}

template <typename T>
inline bool operator >=(const sf::Vector3<T>& a, const sf::Vector3<T>& b) {
    return b <= a;
}

#endif
#pragma endregion