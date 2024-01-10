#pragma once

#include "defs.h"
#include "hollow.h"

namespace fun::rpc {
    struct connection_stub_t;
    struct packet_storage_t;
    struct serializer_t;
    struct deserializer_t;
    struct remote_storage_t;

    struct i_rpc_t;

    struct i_invoker_t {
    protected:
        typedef std::function<void(fun::rpc::deserializer_t&, fun::rpc::i_hollow_t*, serializer_t&)> invoker_fn_t;

    public:
        ~i_invoker_t() = default;

        virtual void invoke(deserializer_t&, i_hollow_t*, serializer_t&) = 0;
        virtual void register_interface(iid_t, invoker_fn_t) = 0;
    };

    struct i_local_storage_t {
        ~i_local_storage_t() = default;

        virtual void serialize_object(key_t, serializer_t&) = 0;
        virtual void store_object(key_t, i_hollow_t*) = 0;
    };

    struct i_stub_factory_t {
    protected:
        typedef std::function<i_hollow_t*(addr_t, oid_t, i_rpc_t&)> factory_fn_t;

    public:
        ~i_stub_factory_t() = default;

        virtual i_hollow_t* create(iid_t, addr_t, oid_t) = 0;
        virtual void register_interface(iid_t, factory_fn_t) = 0;
    };

    struct i_connection_provider_t {
        virtual ~i_connection_provider_t() = default;

        virtual void init(port_t) = 0;
        virtual void quit() = 0;

        virtual addr_t get_pub_addr() = 0;
        virtual addr_t get_loc_addr() = 0;

        virtual connection_stub_t get_connection(addr_t) = 0;
        virtual bool check_connection(addr_t) = 0;

        virtual void check_for_incoming_connections() = 0;
        virtual void check_for_incoming_data() = 0;

        virtual packet_storage_t& get_packet_storage() = 0;
    };

    struct i_rpc_t {
        virtual ~i_rpc_t() = default;

        virtual void init(port_t port) = 0;
        virtual void quit() = 0;

        virtual void step() = 0;
        virtual void run() = 0;

        virtual i_connection_provider_t& get_connection_provider() = 0;
        virtual i_stub_factory_t& get_stub_factory() = 0;
        virtual i_local_storage_t& get_local_storage() = 0;
        virtual i_invoker_t& get_invoker() = 0;
    };
};