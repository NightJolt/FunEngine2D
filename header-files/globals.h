#pragma once



#define INIT_SCREEN_SIZE sf::Vector2i(1920, 1440)
#define INIT_VIEW_SIZE sf::Vector2f(1920, 1440)
#define INIT_VIEW_ORIGIN Vector2f(0, 0)

#define CHUNK_SIZE 16

#define TILE_SIZE 8.f
#define TILE_TEXTURE_SIZE 8
#define TILE_ATLAS_SIZE 256
#define RAND_TEXTURE_COUNT 2


struct UniqueKey {
    UniqueKey(void* p, std::string k) : ptr(p), key(k) {}

    void* ptr;
    std::string key;

    bool operator <(const UniqueKey& u_k) const {
        return key < u_k.key;
    }
};



template <typename T>
std::string to_string_unformatted(const sf::Vector2<T>& a) {
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

template <class T>
T** init_2d_ptr_arr(const unsigned int &x, const unsigned int &y) {
    T** arr = new T*[x];

    for (T** t = arr; t != arr + x; t++) {
        *t = new T[y];

        for (int i = 0; i != y; i++) {
            *(*t + i) = T();
        }
    }

    return arr;
}

template <class T>
void del_2d_ptr_arr(T** arr, const unsigned int& x) {
    for (T** t = arr; t != arr + x; t++) {
        delete[] *t;
    }

    delete[] arr;
}

template <class T>
void cpy_2d_ptr_arr(T** f, T** t, const unsigned int& x, const unsigned int &y) {
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            t[i][j] = f[i][j];
        }
    }
}