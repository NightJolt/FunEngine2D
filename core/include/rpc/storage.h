#pragma once

#include "defs.h"
#include "connection.h"
#include "serialize.h"
#include "interfaces.h"
#include "sync.h"
#include "stub.h"

namespace fun::rpc {
    class remote_storage_t {
    public:
        remote_storage_t(i_rpc_t&, addr_t);

        template <class T>
        stub_t<T>* request_object(key_t key) {
            rpc_scope_lock_t lock(rpc);

            return static_cast<stub_t<T>*>(request_unknown(T::iid, key));
        }

    private:
        i_hollow_t* request_unknown(iid_t, key_t);

        i_rpc_t& rpc;
        addr_t addr;
    };

    class local_storage_t : public i_local_storage_t {
    public:
        local_storage_t() = default;
        ~local_storage_t() = default;

        local_storage_t(const local_storage_t&) = delete;
        local_storage_t& operator=(const local_storage_t&) = delete;

        local_storage_t(local_storage_t&&) noexcept = delete;
        local_storage_t& operator=(local_storage_t&&) noexcept = delete;

        void serialize_object(key_t, serializer_t&) override;
        void store_object(key_t, i_hollow_t*) override;

    private:
        std::unordered_map<key_t, oid_t> storage;
    };
}