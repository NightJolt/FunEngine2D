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
        virtual ~stub_t() = default;

        bool is_valid() {
            return connection_provider.check_connection(owner_addr);
        }

    protected:
        addr_t owner_addr;
        oid_t owner_oid;
        connection_provider_t& connection_provider;
    };

    class stub_factory_t {
    public:
        i_hollow_t* create(iid_t, addr_t, oid_t, connection_provider_t&);
        void register_interface(iid_t, std::function<i_hollow_t*(fun::rpc::addr_t, fun::rpc::oid_t, fun::rpc::connection_provider_t&)>);

    private:
        std::unordered_map<iid_t, std::function<i_hollow_t*(fun::rpc::addr_t, fun::rpc::oid_t, fun::rpc::connection_provider_t&)>> factories;
    };
}