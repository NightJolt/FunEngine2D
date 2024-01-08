#pragma once

#include "../globals.h"
#include "../uuid.h"

#include "serialize.h"
#include "connection.h"
#include "storage.h"
#include "invoker.h"
#include "stub.h"

namespace fun::rpc {
    class rpc_t {
    public:
        void init(port_t port);
        void quit();

        void step();
        void run();

        connection_provider_t& get_connection_provider();
        stub_factory_t& get_stub_factory();
        remote_storage_t get_remote_storage(addr_t);
        local_storage_t& get_local_storage();
        invoker_t& get_invoker();

    private:
        void process_connections();
        void process_packet(packet_t&);
        void process_packets();

        connection_provider_t connection_provider;
        local_storage_t local_storage;
        invoker_t invoker;
        stub_factory_t stub_factory;
    };
}