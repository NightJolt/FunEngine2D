#pragma once

#include "../globals.h"
#include "../uuid.h"

#include "interfaces.h"
#include "serialize.h"
#include "connection.h"
#include "storage.h"
#include "invoker.h"
#include "stub.h"

namespace fun::rpc {
    class rpc_t : public i_rpc_t {
    public:
        void init(port_t port) override;
        void quit() override;

        void step() override;
        void run() override;

        i_connection_provider_t& get_connection_provider() override;
        i_stub_factory_t& get_stub_factory() override;
        i_local_storage_t& get_local_storage() override;
        i_invoker_t& get_invoker() override;

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