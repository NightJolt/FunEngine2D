#pragma once

#include "globals.h"

namespace fun {
    template <class T>
    struct vec2_t {
        T x, y;

        vec2_t();
        vec2_t(T);
        vec2_t(T, T);

        template <class U>
        vec2_t(const vec2_t<U>&);

#if defined(FE2D_SFML)
        vec2_t(sf::Vector2<T>);
        sf::Vector2<T> to_sf() const;
        operator sf::Vector2<T>() const;
#endif

#if defined(FE2D_BOX2D)
        vec2_t(b2Vec2);
        b2Vec2 to_b2() const;
#endif
    };

    typedef vec2_t <int32_t> vec2i_t;
    typedef vec2_t <uint32_t> vec2u_t;
    typedef vec2_t <float> vec2f_t;
    typedef vec2_t <double> vec2d_t;

    typedef vec2_t <int8_t> vec2i8_t;
    typedef vec2_t <int16_t> vec2i16_t;
    typedef vec2_t <int32_t> vec2i32_t;
    typedef vec2_t <int64_t> vec2i64_t;

    typedef vec2_t <uint8_t> vec2u8_t;
    typedef vec2_t <uint16_t> vec2u16_t;
    typedef vec2_t <uint32_t> vec2u32_t;
    typedef vec2_t <uint64_t> vec2u64_t;
}

namespace fun {
    template <class T>
    std::string to_string(vec2_t <T> v) {
        return "vec2(" + std::to_string(v.x) + ", " + std::to_string(v.y) + ")";
    }
    
    template <class T>
    size_t hash(vec2_t <T> v) {
        return (v.x + v.y) * (v.x + v.y + 1) >> 1 + v.x;
    };

    template <class Key>
    struct vec2_hasher_t {
        size_t operator()(vec2_t <Key> v) const {
            return hash(v);
        }
    };

    template <class Key>
    struct vec2_comparer_t {
        bool operator()(vec2_t <Key> a, vec2_t <Key> b) const {
            return a.x == b.x && a.y == b.y;
        }
    };

    // template <class Key>
    // using vec2_hasher_t = decltype([](const vec2_t <Key>& v) -> size_t const { return hash(v); });

    // template <class Key>
    // using vec2_comparer_t = decltype([](const vec2_t <Key>&a, const vec2_t <Key>& b) -> bool const { return a == b; });

    template <class Key, class Value>
    using unordered_map_vec2_t = std::unordered_map <
            vec2_t <Key>,
            Value,
            vec2_hasher_t <Key>,//vec2_hasher_lambda <Key>,
            vec2_comparer_t <Key>//vec2_comparer_lambda <Key>
        >;
}

template <class T>
fun::vec2_t<T>::vec2_t() : x(0), y(0) {}

template <class T>
fun::vec2_t<T>::vec2_t(T x) : x(x), y(x) {}

template <class T>
fun::vec2_t<T>::vec2_t(T x, T y) : x(x), y(y) {}

template <class T>
template <class U>
fun::vec2_t<T>::vec2_t(const vec2_t<U>& vec2) : x((T)vec2.x), y((T)vec2.y) {}


#if defined(FE2D_SFML)
template <class T>
fun::vec2_t<T>::vec2_t(sf::Vector2<T> sf_vec2) : x(sf_vec2.x), y(sf_vec2.y) {}

template <class T>
sf::Vector2<T> fun::vec2_t<T>::to_sf() const {
    return sf::Vector2 <T> (x, y);
}

template <class T>
fun::vec2_t<T>::operator sf::Vector2<T>() const {
    return to_sf();
}
#endif


#if defined(FE2D_BOX2D)
template <class T>
fun::vec2_t<T>::vec2_t(b2Vec2 b2_vec2) : x(b2_vec2.x), y(b2_vec2.y) {}

template <class T>
b2Vec2 fun::vec2_t<T>::to_b2() const {
    return b2Vec2(x, y);
}
#endif


template <typename T>
inline bool operator ==(const fun::vec2_t<T>& a, const fun::vec2_t<T>& b) {
    return a.x == b.x && a.y == b.y;
}

template <typename T>
inline bool operator !=(const fun::vec2_t<T>& a, const fun::vec2_t<T>& b) {
    return a.x != b.x || a.y != b.y;
}

#if defined(FE2D_DEBUG)
template <typename T>
inline std::ostream& operator <<(std::ostream& out, const fun::vec2_t<T>& vec2) {
    return out << fun::to_string(vec2);
}
#endif

template <typename T>
inline fun::vec2_t<T> operator *(const fun::vec2_t<T>& a, const fun::vec2_t<T>& b) {
    return fun::vec2_t <T> (a.x * b.x, a.y * b.y);
}

template <typename T>
inline void operator *=(fun::vec2_t<T>& a, const fun::vec2_t<T>& b) {
    a = a * b;
}

template <typename T>
inline fun::vec2_t<T> operator *(const fun::vec2_t<T>& a, const T& b) {
    return fun::vec2_t <T> (a.x * b, a.y * b);
}

template <typename T>
inline void operator *=(fun::vec2_t<T>& a, const T& b) {
    a = a * b;
}

template <typename T>
inline fun::vec2_t<T> operator /(const fun::vec2_t<T>& a, const fun::vec2_t<T>& b) {
    return fun::vec2_t <T> (a.x / b.x, a.y / b.y);
}

template <typename T>
inline void operator /=(fun::vec2_t<T>& a, const fun::vec2_t<T>& b) {
    a = a / b;
}

template <typename T>
inline fun::vec2_t<T> operator /(const fun::vec2_t<T>& a, const T& b) {
    return fun::vec2_t <T> (a.x / b, a.y / b);
}

template <typename T>
inline void operator /=(fun::vec2_t<T>& a, const T& b) {
    a = a / b;
}

template <typename T>
inline fun::vec2_t<T> operator %(const fun::vec2_t<T>& a, const T& b) {
    return fun::vec2_t <T> (a.x % b, a.y % b);
}

template <typename T>
inline void operator %=(fun::vec2_t<T>& a, const T& b) {
    a = a % b;
}

template <typename T>
inline fun::vec2_t<T> operator +(const fun::vec2_t<T>& a, const fun::vec2_t<T>& b) {
    return fun::vec2_t <T> (a.x + b.x, a.y + b.y);
}

template <typename T>
inline void operator +=(fun::vec2_t<T>& a, const fun::vec2_t<T>& b) {
    a = a + b;
}

template <typename T>
inline fun::vec2_t<T> operator +(const fun::vec2_t<T>& a, const T& b) {
    return fun::vec2_t <T> (a.x + b, a.y + b);
}

template <typename T>
inline void operator +=(fun::vec2_t<T>& a, const T& b) {
    a = a + b;
}

template <typename T>
inline fun::vec2_t<T> operator -(const fun::vec2_t<T>& a, const fun::vec2_t<T>& b) {
    return fun::vec2_t <T> (a.x - b.x, a.y - b.y);
}

template <typename T>
inline void operator -=(fun::vec2_t<T>& a, const fun::vec2_t<T>& b) {
    a = a - b;
}

template <typename T>
inline fun::vec2_t<T> operator -(const fun::vec2_t<T>& a, const T& b) {
    return fun::vec2_t <T> (a.x - b, a.y - b);
}

template <typename T>
inline void operator -=(fun::vec2_t<T>& a, const T& b) {
    a = a - b;
}

// template <typename T>
// inline bool operator <(const fun::vec2_t<T>& a, const fun::vec2_t<T>& b) {
//     return a.x < b.x && a.y < b.y;
// }

// template <typename T>
// inline bool operator <=(const fun::vec2_t<T>& a, const fun::vec2_t<T>& b) {
//     return a < b || a == b;
// }

// template <typename T>
// inline bool operator >(const fun::vec2_t<T>& a, const fun::vec2_t<T>& b) {
//     return b < a;
// }

// template <typename T>
// inline bool operator >=(const fun::vec2_t<T>& a, const fun::vec2_t<T>& b) {
//     return b <= a;
// }
