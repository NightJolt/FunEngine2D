#pragma once

#include "../globals.h"

#include "serialize.h"
#include "connection.h"
#include "storage.h"

namespace fun::rpc {
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

        local_storage_t& get_local_storage() {
            return local_storage;
        }

        void step() {
            process_connections();
            process_packets();
        }

        void run() {
            while (true) {
                step();
            }
        }

    private:
        void process_connections() {
            connection_provider.check_for_incoming_connections();
            connection_provider.check_for_incoming_data();
        }

        void process_packet(packet_t& packet) {
            deserializer_t deserializer(packet.get_data());

            uint32_t call_type = deserializer.deserialize<uint32_t>();
            uint32_t request_type = deserializer.deserialize<uint32_t>();
            key_t key = deserializer.deserialize<key_t>();

            if (request_type == 0) {
                serializer_t serializer;
                local_storage.serialize_object(key, serializer);
                 
                auto connection = connection_provider.get_connection(packet.get_sender_addr());
                if (connection.is_valid()) {
                    connection.send(serializer.get_data(), serializer.get_size());
                }
            }
        }

        void process_packets() {
            auto& packets = connection_provider.get_packet_storage();

            while (!packets.empty()) {
                auto packet = packets.pop();

                process_packet(packet);
            }
        }

        connection_provider_t connection_provider;
        local_storage_t local_storage;
    };
}