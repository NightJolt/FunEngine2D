#pragma once

#include "defs.h"
#include "connection.h"
#include "serialize.h"
#include "hollow.h"

namespace fun::rpc {
    class remote_storage_t {
    public:
        remote_storage_t(addr_t addr, connection_provider_t& connection_provider) : addr(addr), connection_provider(connection_provider) {}

        template <class T>
        T request_object(key_t key) {
            serializer_t serializer;

            serializer.serialize<oid_t>(0); // non object call
            serializer.serialize<mid_t>(0); // request stub
            serializer.serialize<key_t>(key); // storage object key

            auto connection = connection_provider.get_connection(addr);
            
            if (connection.is_valid()) {
                connection.send(serializer.get_data(), serializer.get_size());
            }

            oid_t oid = 0;
            uint32_t packed_ind = 0;
            auto& packet_storage = connection_provider.get_packet_storage();

            while (true) {
                connection_provider.check_for_incoming_data();

                bool found = false;
                
                while (packed_ind < packet_storage.get_size()) {
                    auto& packet = packet_storage[packed_ind];

                    deserializer_t deserializer(packet.get_data());

                    oid_t call_type = deserializer.deserialize<oid_t>();

                    if (call_type == 0) {
                        mid_t answer_type = deserializer.deserialize<mid_t>();

                        if (answer_type == 1) {
                            oid = deserializer.deserialize<oid_t>();
                            found = true;

                            packet_storage.remove(packed_ind);

                            break;
                        }
                    }

                    packed_ind++;
                }

                if (found) {
                    break;
                }
            }

            return T(addr, oid);
        }

    private:
        addr_t addr;
        connection_provider_t& connection_provider;
    };

    class local_storage_t {
    public:
        local_storage_t() = default;
        ~local_storage_t() = default;

        local_storage_t(const local_storage_t&) = delete;
        local_storage_t& operator=(const local_storage_t&) = delete;

        local_storage_t(local_storage_t&& other) noexcept = delete;
        local_storage_t& operator=(local_storage_t&& other) noexcept = delete;

        void serialize_object(key_t key, serializer_t& serializer) {
            serializer.serialize<oid_t>(0); // non object call
            serializer.serialize<mid_t>(1); // stub answer
            serializer.serialize<oid_t>(storage[key]); // object id
        }

        void store_object(key_t key, i_hollow_t* oid) {
            storage[key] = (oid_t)oid;
        }

    private:
        std::unordered_map<key_t, oid_t> storage;
    };

    class object_storage_t {
    public:
        object_storage_t() = default;
        ~object_storage_t() = default;

        object_storage_t(const object_storage_t&) = delete;
        object_storage_t& operator=(const object_storage_t&) = delete;

        object_storage_t(object_storage_t&& other) noexcept = delete;
        object_storage_t& operator=(object_storage_t&& other) noexcept = delete;

        void store(oid_t oid, i_hollow_t* object) {
            objects[oid] = object;
        }

        i_hollow_t* fetch(oid_t oid) {
            return objects[oid];
        }

    private:
        std::unordered_map<oid_t, i_hollow_t*> objects;
    };
}