#include "rpc/packet.h"

fun::rpc::packet_t::packet_t(uint8_t* data, uint32_t size, addr_t sender_addr) : bytes(bytes_t::create(data, size)), sender_addr(sender_addr) {}

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
