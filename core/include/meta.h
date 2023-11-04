#pragma once

namespace fun::meta {
    template <class T>
    struct rank { static constexpr size_t value = 0u; };

    template <class U, size_t N>
    struct rank<U[N]> {
        static constexpr size_t value = rank<U>::value + 1u;
    };

    template <class U>
    struct rank<U[]> {
        static constexpr size_t value = rank<U>::value + 1u;
    };

    template <class T>
    constexpr size_t rank_v = rank<T>::value;
}