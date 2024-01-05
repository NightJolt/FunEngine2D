#include "bytes.h"

fun::bytes_t::bytes_t() : data(nullptr), size(0) {}

fun::bytes_t::bytes_t(bytes_t&& other) noexcept : data(std::exchange(other.data, nullptr)), size(std::exchange(other.size, 0)) {}
fun::bytes_t& fun::bytes_t::operator=(bytes_t&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    data = std::exchange(other.data, nullptr);
    size = std::exchange(other.size, 0);

    return *this;
}

fun::bytes_t fun::bytes_t::clone() const {
    return create(data.get(), size);
}

uint8_t& fun::bytes_t::operator[](uint32_t index) {
    return data[index];
}

void fun::bytes_t::copy_in(uint8_t* in_data, uint32_t in_size, uint32_t offset) {
    data = std::make_unique<uint8_t[]>(in_size);
    size = in_size;

    memcpy(data.get() + offset, in_data, size);
}

void fun::bytes_t::copy_out(uint8_t* out_data, uint32_t out_size, uint32_t offset) const {
    memcpy(out_data, data.get() + offset, out_size);
}

uint8_t* fun::bytes_t::get_data() {
    return data.get();
}

uint32_t fun::bytes_t::get_size() const {
    return size;
}

fun::bytes_t fun::bytes_t::init(uint8_t* data, uint32_t size) {
    bytes_t bytes;

    bytes.data.reset(data);
    bytes.size = size;

    return bytes;
}

fun::bytes_t fun::bytes_t::create(uint32_t size) {
    bytes_t bytes;
    
    bytes.data = std::make_unique<uint8_t[]>(size);
    bytes.size = size;

    return bytes;
}

fun::bytes_t fun::bytes_t::create(uint8_t* data, uint32_t size) {
    bytes_t bytes;

    bytes.data = std::make_unique<uint8_t[]>(size);
    bytes.size = size;

    memcpy(bytes.data.get(), data, size);

    return bytes;
}

fun::bytes_t fun::bytes_t::create(std::initializer_list<uint8_t> list) {
    bytes_t bytes;

    bytes.data = std::make_unique<uint8_t[]>(list.size());
    bytes.size = list.size();

    memcpy(bytes.data.get(), list.begin(), list.size());

    return bytes;
}

fun::bytes_t fun::bytes_t::create(const std::string& string) {
    bytes_t bytes;

    bytes.data = std::make_unique<uint8_t[]>(string.size());
    bytes.size = string.size();

    memcpy(bytes.data.get(), string.data(), string.size());

    return bytes;
}
