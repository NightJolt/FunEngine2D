#pragma once

#include "defs.h"
#include "connection.h"
#include "hollow.h"

namespace fun::rpc {
    template <class intref_t>
    class stub_t : public intref_t {
    public:
        stub_t(addr_t owner_addr, oid_t owner_oid, connection_provider_t& connection_provider) :
            owner_addr(owner_addr), owner_oid(owner_oid), connection_provider(connection_provider) {}

    protected:
        addr_t owner_addr;
        oid_t owner_oid;
        connection_provider_t& connection_provider;
    };

    class stub_factory_t {
    public:
        i_hollow_t* create(iid_t iid, addr_t owner_addr, oid_t owner_oid, connection_provider_t& connection_provider) {
            return factories[iid](owner_addr, owner_oid, connection_provider);
        }

        void register_interface(iid_t iid, std::function<i_hollow_t*(fun::rpc::addr_t, fun::rpc::oid_t, fun::rpc::connection_provider_t&)> factory) {
            factories[iid] = factory;
        }

    private:
        std::unordered_map<iid_t, std::function<i_hollow_t*(fun::rpc::addr_t, fun::rpc::oid_t, fun::rpc::connection_provider_t&)>> factories;
    };
}