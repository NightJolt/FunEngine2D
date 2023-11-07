#pragma once

#include "../globals.h"

#include "hollow.h"
#include "serializer.h"
#include "connection.h"

namespace fun::rpc {
    class remote_storage_t {
    public:
        remote_storage_t(addr_t addr, connection_provider_t& connection_provider) : addr(addr), connection_provider(connection_provider) {}

        template <class T>
        void request_object(key_t key) {
            serializer_t serializer;

            serializer.serialize(0); // non object call
            serializer.serialize(0); // request stub
            serializer.serialize(key); // storage object key

            auto connection = connection_provider.get_connection(addr);
            
            if (connection.is_valid()) {
                connection.send(serializer.get_data(), serializer.get_size());
            }
        }

    private:
        addr_t addr;
        connection_provider_t& connection_provider;
    };
    
    class rpc_t {
    public:
        void init(port_t port) {
            connection_provider.init(port);
        }

        void quit() {
            connection_provider.quit();
        }

        connection_stub_t get_connection(addr_t addr) {
            return connection_provider.get_connection(addr);
        }

        remote_storage_t get_remote_storage(addr_t addr) {
            return remote_storage_t(addr, connection_provider);
        }

        void step() {
            connection_provider.check_for_incoming_connections();
        }

        void run() {
            while (true) {
                step();
            }
        }

    private:
        connection_provider_t connection_provider;
    };
}