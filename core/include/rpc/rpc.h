#pragma once

#include "../globals.h"

#include "hollow.h"
#include "serialize.h"
#include "connection.h"

namespace fun::rpc {
    class remote_storage_t {
    public:
        remote_storage_t(addr_t addr, connection_provider_t& connection_provider) : addr(addr), connection_provider(connection_provider) {}

        template <class T>
        void request_object(key_t key) {
            serializer_t serializer;

            serializer.serialize<uint32_t>(0); // non object call
            serializer.serialize<uint32_t>(0); // request stub
            serializer.serialize<key_t>(key); // storage object key

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
                serializer.serialize<uint32_t>(0); // non object call
                serializer.serialize<uint32_t>(1); // stub answer
                serializer.serialize<key_t>(key); // object id

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
    };
}