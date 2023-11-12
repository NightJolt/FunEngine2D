#pragma once

#include "../globals.h"

namespace fun::rpc {
    typedef uint64_t iid_t; // * interface id
    typedef uint64_t oid_t; // * object id
    typedef uint32_t mid_t; // * method id

    typedef uint64_t key_t;

    typedef uint32_t ip_t;
    typedef uint16_t port_t;

    struct addr_t {
        addr_t() : ip(0), port(0) {}
        addr_t(ip_t ip, port_t port) : ip(ip), port(port) {}

        ip_t ip;
        port_t port;
    };
}