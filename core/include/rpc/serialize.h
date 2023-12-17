#pragma once

#include "../globals.h"
#include "../bytes.h"
#include "../color.h"

namespace fun::rpc {
    template <class T>
    concept STR_T = std::is_same_v<T, std::string>;

    template <class T>
    concept INT_T = std::is_integral_v<T>;

    template <class T>
    concept BYTES_T = std::is_same_v<T, bytes_t>;

    template <template <class...> class V, class T>
    concept VEC_T = std::is_same_v<V<T>, std::vector<T>>;

    template <class T>
    concept COL_T = std::is_same_v<T, rgb_t> || std::is_same_v<T, rgba_t>;

    class serializer_t {
    public:
        serializer_t();
        ~serializer_t() = default;

        serializer_t(const serializer_t&) = delete;
        serializer_t& operator=(const serializer_t&) = delete;

        serializer_t(serializer_t&&) noexcept = delete;
        serializer_t& operator=(serializer_t&&) noexcept = delete;

        template <INT_T INT>
        void serialize(INT value) {
            *(INT*)cursor = value;
            cursor += sizeof(INT);
        }
        
        template <STR_T>
        void serialize(const std::string& value) {
            serialize<uint32_t>(value.size());
            memcpy(cursor, value.data(), value.size());
            cursor += value.size();
        }

        template <BYTES_T>
        void serialize(const bytes_t& value) {
            serialize<uint32_t>(value.get_size());
            value.copy_out(cursor, value.get_size());
            cursor += value.get_size();
        }

        template <template <class...> class V, class T>
        requires VEC_T<V, T>
        void serialize(const std::vector<T>& value) {
            serialize<uint32_t>(value.size());

            for (const auto& item : value) {
                serialize<T>(item);
            }
        }

        template <COL_T col_t>
        void serialize(const col_t& value) {
            serialize<uint8_t>(value.r);
            serialize<uint8_t>(value.g);
            serialize<uint8_t>(value.b);

            if constexpr (requires { value.a; }) {
                serialize<uint8_t>(value.a);
            }
        }

        uint8_t* get_data();
        uint32_t get_size();

    private:
        uint8_t data[256];
        uint8_t* cursor;
    };

    class deserializer_t {
    public:
        deserializer_t(uint8_t*);

        template <INT_T INT>
        INT deserialize() {
            INT value = *(INT*)cursor;
            cursor += sizeof(INT);

            return value;
        }

        template <STR_T>
        std::string deserialize() {
            uint32_t size = deserialize<uint32_t>();
            std::string value((char*)cursor, size);
            cursor += size;

            return value;
        }

        template <BYTES_T>
        bytes_t deserialize() {
            uint32_t size = deserialize<uint32_t>();
            bytes_t value(bytes_t::create(cursor, size));
            cursor += size;

            return value;
        }

        template <template <class...> class V, class T>
        requires VEC_T<V, T>
        std::vector<T> deserialize() {
            uint32_t size = deserialize<uint32_t>();
            std::vector<T> value;

            for (uint32_t i = 0; i < size; i++) {
                value.push_back(deserialize<T>());
            }

            return value;
        }

        template <COL_T col_t>
        col_t deserialize() {
            col_t value;
            
            value.r = deserialize<uint8_t>();
            value.g = deserialize<uint8_t>();
            value.b = deserialize<uint8_t>();

            if constexpr (requires { value.a; }) {
                value.a = deserialize<uint8_t>();
            }

            return value;
        }

    private:
        uint8_t* data;
        uint8_t* cursor;
    };
}