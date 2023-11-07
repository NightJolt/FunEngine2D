#pragma once

#include "../globals.h"

namespace fun::rpc {
    class serializer_t {
    public:
        serializer_t() : cursor(data) {}

        template <class INT_T>
        std::enable_if_t<std::is_integral_v<INT_T>> serialize(INT_T value) {
            memcpy(cursor, &value, sizeof(INT_T));
            cursor += sizeof(INT_T);
        }

        uint8_t* get_data() {
            return data;
        }

        uint32_t get_size() {
            return cursor - data;
        }

    private:
        uint8_t data[128];
        uint8_t* cursor;
    };
}