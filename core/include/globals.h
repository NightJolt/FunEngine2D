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
#define USES_BOX2D

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

#if defined(USES_BOX2D)

#include <box2d/box2d.h>

#endif

#pragma endregion

#pragma region stdlibs

#if defined(ENABLE_DEBUGGING)
#include <iostream>

#define print(body) std::cout << body
#define printsp(body) print(body) << " "
#define println(body) print(body) << std::endl
#define printbr() std::cout << std::endl
#endif

#include <stdint.h>
#include <memory>
#include <cstring>
#include <sstream>
#include <string_view>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <cmath>
#include <vector>
#include <array>
#include <queue>
#include <random>
// #include <xhash>
#include <utility>
#include <functional>
#include <algorithm>
#include <tuple>

#include <any>
#include <variant>
#include <optional>

#include <thread>
#include <future>
#include <mutex>
#include <condition_variable>
#include <semaphore>

#pragma endregion

/*#pragma region tilemap

#define CHUNK_SIZE 16
#define TILE_SIZE 8.f
#define TILE_TEXTURE_SIZE 8
#define TILE_ATLAS_SIZE 256
#define RAND_TEXTURE_COUNT 2

#pragma endregion*/

// typedef char i8;                     //                       -127 to 127
// typedef short i16;                   //                    -32,768 to 32,767
// typedef int i32;                     //             -2,147,483,648 to 2,147,483,647
// typedef long long i64;               // -9,223,372,036,854,775,807 to 9,223,372,036,854,775,807
// typedef long i32_64;
// typedef unsigned char u8;           //                          0 to 255
// typedef unsigned short u16;         //                          0 to 65,535
// typedef unsigned int u32;           //                          0 to 4,294,967,295
// typedef unsigned long long u64;     //                          0 to 18,446,744,073,709,551,615
// typedef unsigned long u32_64;

namespace fun {
    typedef uint64_t mask64_t;
    typedef uint32_t mask32_t;
    typedef uint16_t mask16_t;
    typedef uint8_t mask8_t;

    typedef uint64_t uuid_t;
}

#define M_TO_LAMBDA(type, args, body) [this] args -> type body
#define M_IS_TYPE_OF(type, obj) (dynamic_cast <type*> (obj) != nullptr)

#define M_BITS(expr) (sizeof(expr) << 3)

namespace fun {
    void glob_init();
}

namespace fun {
    template <class T>
    struct Vec2 {
        T x, y;

        Vec2() : x(0), y(0) {}
        Vec2(T x, T y) : x(0), y(0) {}
    };

    typedef Vec2 <int32_t> Vec2i;
    typedef Vec2 <uint32_t> Vec2u;
    typedef Vec2 <float> Vec2f;
}

namespace fun {
    // struct Transform {
    //     Vec2f position;
    //     float rotation;
    //     Vec2f scale;

    //     explicit Transform(Vec2f p = { 0, 0 }, float r = 0, Vec2f s = { 1, 1 }) {
    //         position = p;
    //         rotation = r;
    //         scale = s;
    //     }
    // };

    struct Transform {
        sf::Vector2f position;
        float rotation;

        explicit Transform(sf::Vector2f p = { 0, 0 }, float r = 0) {
            position = p;
            rotation = r;
        }
    };
}

namespace fun {
    namespace uuid {
        uuid_t generate();
    }

    struct UniqueKey {
        UniqueKey();
        UniqueKey(uuid_t, const char*);
        // ~UniqueKey();

        UniqueKey(const UniqueKey&);
        UniqueKey& operator =(const UniqueKey&);
        UniqueKey(UniqueKey&&) noexcept;

		operator uint64_t() const;

        uuid_t uuid;
        char key[16];
    };
}

namespace std {
    template <>
    struct hash <fun::UniqueKey> {
        std::size_t operator()(const fun::UniqueKey& ukey) const {
            size_t h = 5381;
            int c;
            const char* s = ukey.key;

			while ((c = *s++))
				h = ((h << 5) + h) + c;

            return hash <uint64_t> ()(ukey) + h;
        }
    };
}

#pragma region sfml_vec2
#if defined(SFML_VEC2_OVERLOADS)

namespace sf {
    template <typename T>
    inline std::string to_string_key(const sf::Vector2<T>& a) {
        return std::to_string(a.x) + ' ' + std::to_string(a.y);
    }

    template <typename T>
    inline std::string to_string(const sf::Vector2<T>& a) {
        return "V2(" + std::to_string(a.x) + ", " + std::to_string(a.y) + ")";
    }
}

namespace std {
    template <typename T>
    inline std::string to_string(const std::vector<T>& v, function <std::string(size_t, const T&)> converter = [](size_t i, const T& t) -> std::string { return std::to_string(t); }) {
        size_t size = v.size();

        std::string result;

        result.reserve(size * (sizeof(v) + 2));

        result.append("[");

        for (int i = 0; i < size - 1; i++) {
            result.append(converter(i, v[i]));
            result.append(", ");
        }

        if (!v.empty()) result.append(converter(v.size() - 1, v[v.size() - 1]));
        
        result.append("]");

        return result;
    }
}

template <typename T>
inline std::ostream& operator <<(std::ostream& out, const sf::Vector2<T>& a) {
    return out << sf::to_string(a);
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

namespace sf {
    template <typename T>
    std::string to_string_key(const sf::Vector3<T>& a) {
        return std::to_string(a.x) + ' ' + std::to_string(a.y) + ' ' + std::to_string(a.z);
    }

    template <typename T>
    std::string to_string(const sf::Vector3<T>& a) {
        return "V3(" + std::to_string(a.x) + ", " + std::to_string(a.y) + ", " + std::to_string(a.z) + ")";
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