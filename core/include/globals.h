#pragma once

#pragma region flags

#define WIN
// #define UNIX
// #define OSX

#define ENABLE_DEBUGGING
// define RELEASE_BUILD

#define USES_SFML
#define USES_IMGUI
// #define USES_CUDA
// #define USES_LUA
// #define USES_BOX2D

#if defined(USES_SFML)
#define SFML_VEC2_OVERLOADS
#define SFML_VEC3_OVERLOADS
#endif

#pragma endregion

#pragma region libsWW

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

#if defined(ENABLE_DEBUGGING)
#include <iostream>
#endif

#include <memory>
#include <cstring>
#include <sstream>
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

typedef char i8;                     //                       -127 to 127
typedef short i16;                   //                    -32,768 to 32,767
typedef int i32;                     //             -2,147,483,648 to 2,147,483,647
typedef long long i64;               // -9,223,372,036,854,775,807 to 9,223,372,036,854,775,807
typedef long i32_64;
typedef unsigned char u8;           //                          0 to 255
typedef unsigned short u16;         //                          0 to 65,535
typedef unsigned int u32;           //                          0 to 4,294,967,295
typedef unsigned long long u64;     //                          0 to 18,446,744,073,709,551,615
typedef unsigned long u32_64;

#define print(body) std::cout << body
#define printsp(body) print(body) << " "
#define println(body) print(body) << std::endl
#define nextln() std::cout << std::endl

#define to_lambda(type, args, body) [this] args -> type body
#define is_type_of(type, obj) (dynamic_cast <type*> (obj) != nullptr)

namespace fun {
    void glob_init();

    struct UniqueKey {
        UniqueKey(void*, const char*);
        ~UniqueKey();

        bool operator <(const UniqueKey&) const;

        UniqueKey(const UniqueKey&);

        UniqueKey& operator =(const UniqueKey&);

        UniqueKey(UniqueKey&&) noexcept;

        void* ptr;
        char* key;
    };
}

#pragma region sfml_vec2
#if defined(SFML_VEC2_OVERLOADS)

namespace fun {
    template <typename T>
    inline std::string to_string_key(const sf::Vector2<T>& a) {
        return std::to_string(a.x) + ' ' + std::to_string(a.y);
    }

    template <typename T>
    inline std::string to_string(const sf::Vector2<T>& a) {
        return "Vector2(" + std::to_string(a.x) + ", " + std::to_string(a.y) + ")";
    }
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

namespace fun {
    template <typename T>
    std::string to_string_key(const sf::Vector3<T>& a) {
        return std::to_string(a.x) + ' ' + std::to_string(a.y) + ' ' + std::to_string(a.z);
    }

    template <typename T>
    std::string to_string(const sf::Vector3<T>& a) {
        return "Vector3(" + std::to_string(a.x) + ", " + std::to_string(a.y) + ", " + std::to_string(a.z) + ")";
    }
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