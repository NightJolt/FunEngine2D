#pragma once

#include "../globals.h"
#include "defs.h"

namespace fun::rpc {
    class bytes_t {
    public:
        bytes_t() : data(nullptr), size(0) {}
        bytes_t(uint8_t* tmp_data, uint32_t tmp_size) : size(tmp_size) {
            data = std::make_unique<uint8_t[]>(size);
            memcpy(data.get(), tmp_data, size);
        }

        ~bytes_t() = default;

        bytes_t(const bytes_t&) = delete;
        bytes_t& operator=(const bytes_t&) = delete;

        bytes_t(bytes_t&& other) noexcept : data(std::exchange(other.data, nullptr)), size(std::exchange(other.size, 0)) {}
        bytes_t& operator=(bytes_t&& other) noexcept {
            if (this == &other) {
                return *this;
            }

            data = std::exchange(other.data, nullptr);
            size = std::exchange(other.size, 0);

            return *this;
        }

        void copy_in(uint8_t* in_data, uint32_t in_size) {
            data = std::make_unique<uint8_t[]>(in_size);
            size = in_size;

            memcpy(data.get(), in_data, size);
        }

        uint8_t* get_data() {
            return data.get();
        }

        uint32_t get_size() {
            return size;
        }
        
    private:
        std::unique_ptr<uint8_t[]> data;
        uint32_t size;
    };

    class packet_t {
    public:
        packet_t(uint8_t* data, uint32_t size, addr_t sender_addr) : bytes(data, size), sender_addr(sender_addr) {}
        ~packet_t() = default;

        packet_t(const packet_t&) = delete;
        packet_t& operator=(const packet_t&) = delete;

        packet_t(packet_t&& other) noexcept : bytes(std::move(other.bytes)), sender_addr(std::exchange(other.sender_addr, {})) {}
        packet_t& operator=(packet_t&& other) noexcept {
            if (this == &other) {
                return *this;
            }

            bytes = std::move(other.bytes);

            return *this;
        }

        uint8_t* get_data() {
            return bytes.get_data();
        }

        uint32_t get_size() {
            return bytes.get_size();
        }

        addr_t get_sender_addr() {
            return sender_addr;
        }

    private:
        bytes_t bytes;
        addr_t sender_addr;
    };

    class packet_storage_t {
    public:
        void push(uint8_t* data, uint32_t size, addr_t sender_addr) {
            packets.emplace_back(data, size, sender_addr);
        }

        packet_t pop() {
            auto packet = std::move(packets.front());
            packets.erase(packets.begin());

            return packet;
        }

        void remove(uint32_t index) {
            packets.erase(packets.begin() + index);
        }

        packet_t& operator[](uint32_t index) {
            return packets[index];
        }

        uint32_t get_size() {
            return packets.size();
        }

        bool empty() {
            return packets.empty();
        }

    private:
        std::vector<packet_t> packets;
    };
}