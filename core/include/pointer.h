#pragma once

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

    private:

        T* m_ptr;
    };

    // sptr_t
}





fun::uptr_t<class T>::uptr_t() : m_ptr(nullptr) {}

fun::uptr_t<class T>::uptr_t(T* ptr) : m_ptr(ptr) {}

fun::uptr_t<class T>::~uptr_t() {
    delete m_ptr;
}

T* fun::uptr_t<class T>::see() {
    return m_ptr;
}

T* fun::uptr_t<class T>::take() {
    T* ptr = m_ptr;
    m_ptr = nullptr;

    return ptr;
}

void fun::uptr_t<class T>::reset(T* ptr) {
    delete m_ptr;

    m_ptr = ptr;
}