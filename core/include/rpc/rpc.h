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
        void init(port_t port) {
            connection_provider.init(port);
        }

        void quit() {
            connection_provider.quit();
        }

        connection_provider_t& get_connection_provider() {
            return connection_provider;
        }

        stub_factory_t& get_stub_factory() {
            return stub_factory;
        }

        remote_storage_t get_remote_storage(addr_t addr) {
            return remote_storage_t(addr, connection_provider, stub_factory);
        }

        local_storage_t& get_local_storage() {
            return local_storage;
        }

        invoker_t& get_invoker() {
            return invoker;
        }

        template <class T>
        T* create_object() {
            T* obj = new T;

            object_storage.store((oid_t)(i_hollow_t*)obj, obj);

            return obj;
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

            oid_t oid = deserializer.deserialize<oid_t>();

            if (oid == 0) {
                mid_t request_type = deserializer.deserialize<mid_t>();

                if (request_type == 0) {
                    key_t key = deserializer.deserialize<key_t>();

                    serializer_t serializer;
                    local_storage.serialize_object(key, serializer);
                    
                    auto connection = connection_provider.get_connection(packet.get_sender_addr());
                    if (connection.is_valid()) {
                        connection.send(serializer.get_data(), serializer.get_size());
                    }
                }
            } else {
                i_hollow_t* hollow = object_storage.fetch(oid);
                serializer_t serializer;

                invoker.invoke(deserializer, hollow, serializer);

                if (serializer.get_size() > 0) {
                    auto connection = connection_provider.get_connection(packet.get_sender_addr());

                    if (connection.is_valid()) {
                        connection.send(serializer.get_data(), serializer.get_size());
                    }
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
        object_storage_t object_storage;
        invoker_t invoker;
        stub_factory_t stub_factory;
    };
}