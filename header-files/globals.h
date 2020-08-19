#pragma once



#define INIT_SCREEN_SIZE VideoMode(1712, 964)
#define INIT_VIEW_SIZE Vector2f(1712, 964)
#define INIT_VIEW_ORIGIN Vector2f(0, 0)

#define CHUNK_SIZE 16

#define TILE_SIZE 30.f



template <typename T>
std::string to_string(const sf::Vector2<T>& a) {
    return std::to_string(a.x) + ' ' + std::to_string(a.y);
}

template <typename T>
std::ostream& operator <<(std::ostream& out, const sf::Vector2<T>& a) {
    return out << "Vector2(" << a.x << ", " << a.y << ")";
}

template <typename T>
sf::Vector2<T> operator *(const sf::Vector2<T>& a, const sf::Vector2<T>& b) {
    return sf::Vector2<T>(a.x * b.x, a.y * b.y);
}

template <typename T>
sf::Vector2<T> operator *=(sf::Vector2<T>& a, const sf::Vector2<T>& b) {
    a = a * b;
}

template <typename T>
sf::Vector2<T> operator /(const sf::Vector2<T>& a, const sf::Vector2<T>& b) {
    return sf::Vector2<T>(a.x / b.x, a.y / b.y);
}

template <typename T>
sf::Vector2<T> operator /=(sf::Vector2<T>& a, const sf::Vector2<T>& b) {
    a = a / b;
}

template <typename T>
sf::Vector2<T> operator +(const sf::Vector2<T>& a, const T& b) {
    return sf::Vector2<T>(a.x + b, a.y + b);
}

template <typename T>
sf::Vector2<T> operator +=(sf::Vector2<T>& a, const T& b) {
    a = a + b;
}

template <typename T>
sf::Vector2<T> operator -(const sf::Vector2<T>& a, const T& b) {
    return sf::Vector2<T>(a.x - b, a.y - b);
}

template <typename T>
sf::Vector2<T> operator -=(sf::Vector2<T>& a, const T& b) {
    a = a - b;
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