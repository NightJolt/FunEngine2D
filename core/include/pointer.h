#pragma once

#include "meta.h"

namespace fun {
    template <class T>
    class uptr_t {
    public:

        uptr_t();
        uptr_t(T*);

        ~uptr_t();

        T* see();
        T* take();

        void reset(T*);

        operator T*() const;
        T* operator ->() const;

        // copy
        uptr_t(const uptr_t&) = delete;
        uptr_t<T>& operator =(const uptr_t&) = delete;

        // move
        uptr_t(uptr_t&&) noexcept;
        uptr_t<T>& operator =(uptr_t&&) noexcept;

    private:

        T* m_ptr;
    };

    // sptr_t
}



template <class T>
fun::uptr_t<T>::uptr_t() : m_ptr(nullptr) {}


template <class T>
fun::uptr_t<T>::uptr_t(T* ptr) : m_ptr(ptr) {}


template <class T>
fun::uptr_t<T>::~uptr_t() {
    if (meta::rank_v<T> == 0)
        delete m_ptr;
    else
        delete[] m_ptr;
}


template <class T>
T* fun::uptr_t<T>::see() {
    return m_ptr;
}


template <class T>
T* fun::uptr_t<T>::take() {
    T* ptr = m_ptr;
    m_ptr = nullptr;

    return ptr;
}


template <class T>
void fun::uptr_t<T>::reset(T* ptr) {
    if (meta::rank_v<T> == 0)
        delete m_ptr;
    else
        delete[] m_ptr;

    m_ptr = ptr;
}


template <class T>
fun::uptr_t<T>::operator T*() const {
    return m_ptr;
}


template <class T>
T* fun::uptr_t<T>::operator ->() const {
    return m_ptr;
}


template <class T>
fun::uptr_t<T>::uptr_t(uptr_t&& other) noexcept {
    if (this == &other) return;

    m_ptr = other.m_ptr;
    other.m_ptr = nullptr;
}


template <class T>
fun::uptr_t<T>& fun::uptr_t<T>::operator =(uptr_t&& other) noexcept {
    if (this == &other) return *this;

    m_ptr = other.m_ptr;
    other.m_ptr = nullptr;
    
    return *this;
}