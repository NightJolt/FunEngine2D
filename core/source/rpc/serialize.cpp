#include "rpc/serialize.h"

fun::rpc::serializer_t::serializer_t() : cursor(data) {}

uint8_t* fun::rpc::serializer_t::get_data() {
    return data;
}

uint32_t fun::rpc::serializer_t::get_size() {
    return cursor - data;
}

fun::rpc::deserializer_t::deserializer_t(
    uint8_t* data_ptr
) :
    data(data_ptr),
    cursor(data_ptr)
{}
