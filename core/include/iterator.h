#pragma once

#include "globals.h"

namespace fun {
    template <class T>
    class iterator_t {
    public:
        iterator_t() : begin_p(nullptr), end_p(nullptr), ptr(nullptr) {}
        iterator_t(T* begin_p, T* end_p) : begin_p(begin_p), end_p(end_p), ptr(begin_p) {}

        T* begin() { return begin_p; }
        const T* begin() const { return begin_p; }
        T* end() { return end_p; }
        const T* end() const { return end_p; }

    private:
        T* begin_p;
        T* end_p;
        T* ptr;
    };
}
