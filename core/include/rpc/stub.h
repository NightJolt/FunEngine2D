#pragma once

#include "defs.h"
#include "connection.h"
#include "hollow.h"

namespace fun::rpc {
    class stub_factory_t;

    template <class interf_t>
    class stub_t : public interf_t {
    public:
        stub_t(addr_t owner_addr, oid_t owner_oid, connection_provider_t& connection_provider, stub_factory_t& stub_factory) :
            owner_addr(owner_addr), owner_oid(owner_oid), connection_provider(connection_provider), stub_factory(stub_factory) {}
        virtual ~stub_t() = default;

        bool is_valid() {
            return connection_provider.check_connection(owner_addr);
        }

        addr_t owner_addr;
        oid_t owner_oid;

    protected:
        connection_provider_t& connection_provider;
        stub_factory_t& stub_factory;
    };

    class stub_factory_t {
    private:
        typedef std::function<i_hollow_t*(addr_t, oid_t, connection_provider_t&, stub_factory_t&)> factory_fn_t;

    public:
        i_hollow_t* create(iid_t, addr_t, oid_t, connection_provider_t&);
        void register_interface(iid_t, factory_fn_t);

    private:
        std::unordered_map<iid_t, factory_fn_t> factories;
    };
    
    template <class interf_t>
    using rem_ref_t = std::unique_ptr<stub_t<interf_t>>;

    template <class interf_t>
    using ref_t = std::unique_ptr<interf_t>;
}