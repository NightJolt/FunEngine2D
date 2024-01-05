#pragma once

#include "globals.h"

namespace fun {
    class bytes_t {
    public:
        bytes_t();

        ~bytes_t() = default;

        bytes_t(const bytes_t&) = delete;
        bytes_t& operator=(const bytes_t&) = delete;

        bytes_t(bytes_t&&) noexcept;
        bytes_t& operator=(bytes_t&&) noexcept;

        bytes_t clone() const;

        uint8_t& operator[](uint32_t);

        void copy_in(uint8_t*, uint32_t, uint32_t = 0);
        void copy_out(uint8_t*, uint32_t, uint32_t = 0) const;

        uint8_t* get_data();
        uint32_t get_size() const;

        static bytes_t init(uint8_t*, uint32_t);

        static bytes_t create(uint32_t);
        static bytes_t create(uint8_t*, uint32_t);
        static bytes_t create(std::initializer_list<uint8_t>);
        static bytes_t create(const std::string&);
        
    private:
        std::unique_ptr<uint8_t[]> data;
        uint32_t size;
    };
}
