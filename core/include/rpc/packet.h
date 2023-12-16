#pragma once

#include "../globals.h"
#include "defs.h"
#include "../bytes.h"

namespace fun::rpc {
    class packet_t {
    public:
        packet_t(uint8_t*, uint32_t, addr_t);
        ~packet_t() = default;

        packet_t(const packet_t&) = delete;
        packet_t& operator=(const packet_t&) = delete;

        packet_t(packet_t&&) noexcept;
        packet_t& operator=(packet_t&&) noexcept;

        uint8_t* get_data();
        uint32_t get_size();

        addr_t get_sender_addr();

    private:
        bytes_t bytes;
        addr_t sender_addr;
    };

    class packet_storage_t {
    public:
        void push(uint8_t*, uint32_t, addr_t);
        packet_t pop();
        void remove(uint32_t);
        packet_t& operator[](uint32_t);
        uint32_t get_size();
        bool empty();

    private:
        std::vector<packet_t> packets;
    };
}