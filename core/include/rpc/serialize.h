#pragma once

#include "../globals.h"

namespace fun::rpc {
    template <class T>
    concept STR_T = std::is_same_v<T, std::string>;

    template <class T>
    concept INT_T = std::is_integral_v<T>;

    template <class T>
    concept VEC_T = std::is_same_v<T, std::vector<uint8_t>>;

    class serializer_t {
    public:
        serializer_t() : cursor(data) {}
        ~serializer_t() = default;

        serializer_t(const serializer_t&) = delete;
        serializer_t& operator=(const serializer_t&) = delete;

        serializer_t(serializer_t&& other) noexcept = delete;
        serializer_t& operator=(serializer_t&& other) noexcept = delete;

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

        template <VEC_T>
        void serialize(const std::vector<uint8_t>& value) {
            serialize<uint32_t>(value.size());
            memcpy(cursor, value.data(), value.size());
            cursor += value.size();
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

        template <VEC_T>
        std::vector<uint8_t> deserialize() {
            uint32_t size = deserialize<uint32_t>();
            std::vector<uint8_t> value(cursor, cursor + size);
            cursor += size;

            return value;
        }

    private:
        uint8_t* data;
        uint8_t* cursor;
    };
}