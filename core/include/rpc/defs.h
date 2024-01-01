#pragma once

#include "../globals.h"

namespace fun::rpc {
    typedef uint64_t iid_t; // * interface id
    typedef uint64_t oid_t; // * object id
    typedef uint32_t mid_t; // * method id

    /*
    ? not yet implemented
    * returned by async calls
    * can be used for implementing fault tolerance
    */
    typedef uint64_t call_id_t;

    typedef uint64_t key_t;

    typedef uint32_t ip_t;
    typedef uint16_t port_t;

    struct addr_t {
        addr_t();
        addr_t(ip_t, port_t);
        addr_t(const char*, const char*);

        ip_t ip;
        port_t port;
    };

    enum call_type_t : oid_t {
        global = 0,
    };

    enum request_type_t : uint32_t {
        fetch_object = 0,
        sync_call_reply,
        exception,
    };

    enum exception_t {
        object_does_not_exist = 0,
        interface_does_not_exist,
        method_does_not_exist,
        unknown_request_type,
    };
}