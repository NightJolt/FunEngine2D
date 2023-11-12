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

    class local_storage_t {
    public:
        local_storage_t() = default;
        ~local_storage_t() = default;

        local_storage_t(const local_storage_t&) = delete;
        local_storage_t& operator=(const local_storage_t&) = delete;

        local_storage_t(local_storage_t&& other) noexcept = delete;
        local_storage_t& operator=(local_storage_t&& other) noexcept = delete;

        void serialize_object(key_t key, serializer_t& serializer) {
            serializer.serialize<uint32_t>(0); // non object call
            serializer.serialize<uint32_t>(1); // stub answer
            serializer.serialize<key_t>(storage[key]); // object id
        }

        void store_object(key_t key, i_hollow_t* oid) {
            storage[key] = (oid_t)oid;
        }

    private:
        std::unordered_map<key_t, oid_t> storage;
    };
}