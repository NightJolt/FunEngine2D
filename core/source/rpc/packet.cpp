#include "rpc/packet.h"

fun::rpc::bytes_t::bytes_t() : data(nullptr), size(0) {}
fun::rpc::bytes_t::bytes_t(uint8_t* tmp_data, uint32_t tmp_size) : size(tmp_size) {
    data = std::make_unique<uint8_t[]>(size);
    memcpy(data.get(), tmp_data, size);
}

fun::rpc::bytes_t::bytes_t(bytes_t&& other) noexcept : data(std::exchange(other.data, nullptr)), size(std::exchange(other.size, 0)) {}
fun::rpc::bytes_t& fun::rpc::bytes_t::operator=(bytes_t&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    data = std::exchange(other.data, nullptr);
    size = std::exchange(other.size, 0);

    return *this;
}

void fun::rpc::bytes_t::copy_in(uint8_t* in_data, uint32_t in_size) {
    data = std::make_unique<uint8_t[]>(in_size);
    size = in_size;

    memcpy(data.get(), in_data, size);
}

uint8_t* fun::rpc::bytes_t::get_data() {
    return data.get();
}

uint32_t fun::rpc::bytes_t::get_size() {
    return size;
}

fun::rpc::packet_t::packet_t(uint8_t* data, uint32_t size, addr_t sender_addr) : bytes(data, size), sender_addr(sender_addr) {}

fun::rpc::packet_t::packet_t(packet_t&& other) noexcept : bytes(std::move(other.bytes)), sender_addr(std::exchange(other.sender_addr, {})) {}
fun::rpc::packet_t& fun::rpc::packet_t::operator=(packet_t&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    bytes = std::move(other.bytes);

    return *this;
}

uint8_t* fun::rpc::packet_t::get_data() {
    return bytes.get_data();
}

uint32_t fun::rpc::packet_t::get_size() {
    return bytes.get_size();
}

fun::rpc::addr_t fun::rpc::packet_t::get_sender_addr() {
    return sender_addr;
}

void fun::rpc::packet_storage_t::push(uint8_t* data, uint32_t size, addr_t sender_addr) {
    packets.emplace_back(data, size, sender_addr);
}

fun::rpc::packet_t fun::rpc::packet_storage_t::pop() {
    auto packet = std::move(packets.front());
    packets.erase(packets.begin());

    return packet;
}

void fun::rpc::packet_storage_t::remove(uint32_t index) {
    packets.erase(packets.begin() + index);
}

fun::rpc::packet_t& fun::rpc::packet_storage_t::operator[](uint32_t index) {
    return packets[index];
}

uint32_t fun::rpc::packet_storage_t::get_size() {
    return packets.size();
}

bool fun::rpc::packet_storage_t::empty() {
    return packets.empty();
}
