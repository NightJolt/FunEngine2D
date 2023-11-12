#pragma once

#include "../globals.h"

namespace fun::rpc {
    class serializer_t {
    public:
        serializer_t() : cursor(data) {}

        template <class INT_T>
        std::enable_if_t<std::is_integral_v<INT_T>> serialize(INT_T value) {
            *(INT_T*)cursor = value;
            cursor += sizeof(INT_T);
        }

        uint8_t* get_data() {
            return data;
        }

        uint32_t get_size() {
            return cursor - data;
        }

    private:
        uint8_t data[256];
        uint8_t* cursor;
    };

    class deserializer_t {
    public:
        deserializer_t(uint8_t* d) : data(d) {
            cursor = d;
        }

        template <class INT_T, class TRUE_INT_T = std::remove_cv_t<INT_T>>
        std::enable_if_t<std::is_integral_v<INT_T>, TRUE_INT_T> deserialize() {
            TRUE_INT_T value = *(TRUE_INT_T*)cursor;
            cursor += sizeof(TRUE_INT_T);

            return value;
        }

    private:
        uint8_t* data;
        uint8_t* cursor;
    };
}