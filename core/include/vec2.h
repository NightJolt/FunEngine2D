#pragma once

#include "globals.h"

namespace fun {
    template <class T>
    struct vec2_t {
        T x, y;

        vec2_t();
        vec2_t(T, T);

        template <class U>
        vec2_t(const vec2_t<U>&);

#if defined(USES_SFML)
        vec2_t(sf::Vector2<T>);
        sf::Vector2<T> to_sf() const;
#endif

#if defined(USES_BOX2D)
        vec2_t(b2Vec2);
        b2Vec2 to_b2() const;
#endif
    };

    typedef vec2_t <int32_t> vec2i_t;
    typedef vec2_t <uint32_t> vec2u_t;
    typedef vec2_t <float> vec2f_t;
}

namespace fun {
    template <class T>
    std::string to_string(vec2_t<T> vec2) {
        return "vec2(" + std::to_string(vec2.x) + ", " + std::to_string(vec2.y) + ")";
    }
}


template <class T>
fun::vec2_t<T>::vec2_t() : x(0), y(0) {}

template <class T>
fun::vec2_t<T>::vec2_t(T x, T y) : x(x), y(y) {}

template <class T>
template <class U>
fun::vec2_t<T>::vec2_t(const vec2_t<U>& vec2) : x((T)vec2.x), y((T)vec2.y) {}


#if defined(USES_SFML)
template <class T>
fun::vec2_t<T>::vec2_t(sf::Vector2<T> sf_vec2) : x(sf_vec2.x), y(sf_vec2.y) {}

template <class T>
sf::Vector2<T> fun::vec2_t<T>::to_sf() const {
    return sf::Vector2 <T> (x, y);
}
#endif


#if defined(USES_BOX2D)
template <class T>
fun::vec2_t<T>::vec2_t(b2Vec2 b2_vec2) : x(b2_vec2.x), y(b2_vec2.y) {}

template <class T>
b2Vec2 fun::vec2_t<T>::to_b2() const {
    return b2Vec2(x, y);
}
#endif


template <typename T>
inline std::ostream& operator <<(std::ostream& out, const fun::vec2_t<T>& vec2) {
    return out << fun::to_string(vec2);
}

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
    return vec2_t <T> (a.x / b.x, a.y / b.y);
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
