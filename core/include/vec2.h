#pragma once

#include "Globals.h"

namespace fun {
    template <class T>
    struct vec2_t {
        T x, y;

        vec2_t();
        vec2_t(T, T);

#if defined(USES_SFML)
        vec2_t(sf::Vector2<T>);
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


#if defined(USES_SFML)

template <class T>
fun::vec2_t<T>::vec2_t(sf::Vector2<T> sf_vec2) : x(sf_vec2.x), y(sf_vec2.y) {}

#endif


template <typename T>
inline std::ostream& operator <<(std::ostream& out, const fun::vec2_t<T>& vec2) {
    return out << fun::to_string(vec2);
}

template <typename T>
inline fun::vec2_t<T> operator *(const fun::vec2_t<T>& a, const fun::vec2_t<T>& b) {
    return sf::vec2_t <T> (a.x * b.x, a.y * b.y);
}

template <typename T>
inline void operator *=(fun::vec2_t<T>& a, const fun::vec2_t<T>& b) {
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
inline fun::vec2_t<T> operator +(const fun::vec2_t<T>& a, const T& b) {
    return fun::vec2_t <T> (a.x + b, a.y + b);
}

template <typename T>
inline void operator +=(fun::vec2_t<T>& a, const T& b) {
    a = a + b;
}

template <typename T>
inline fun::vec2_t<T> operator -(const fun::vec2_t<T>& a, const T& b) {
    return fun::vec2_t <T> (a.x - b, a.y - b);
}

template <typename T>
inline void operator -=(fun::vec2_t<T>& a, const T& b) {
    a = a - b;
}

template <typename T>
inline bool operator <(const fun::vec2_t<T>& a, const fun::vec2_t<T>& b) {
    return a.x < b.x && a.y < b.y;
}

template <typename T>
inline bool operator <=(const fun::vec2_t<T>& a, const fun::vec2_t<T>& b) {
    return a < b || a == b;
}

template <typename T>
inline bool operator >(const fun::vec2_t<T>& a, const fun::vec2_t<T>& b) {
    return b < a;
}

template <typename T>
inline bool operator >=(const fun::vec2_t<T>& a, const fun::vec2_t<T>& b) {
    return b <= a;
}
