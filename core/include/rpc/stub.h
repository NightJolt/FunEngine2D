#pragma once

#include "defs.h"
#include "connection.h"
#include "interfaces.h"

namespace fun::rpc {
    class stub_factory_t;

    template <class interf_t>
    class stub_t : public interf_t {
    public:
        stub_t(addr_t owner_addr, oid_t owner_oid, i_rpc_t& rpc) :
            owner_addr(owner_addr), owner_oid(owner_oid), rpc(rpc) {}
        virtual ~stub_t() = default;

        bool is_valid() {
            return rpc.get_connection_provider().check_connection(owner_addr);
        }

        addr_t owner_addr;
        oid_t owner_oid;
        i_rpc_t& rpc;
    };

    class stub_factory_t : public i_stub_factory_t {
    public:
        i_hollow_t* create(iid_t, addr_t, oid_t) override;
        void register_interface(iid_t, factory_fn_t) override;

    private:
        std::unordered_map<iid_t, factory_fn_t> factories;
    };

    template <class interf_t>
    using ref_t = std::unique_ptr<interf_t>;

    template<class interf_t>
    bool check_remote_object_reference(ref_t<interf_t>& obj) {
        return static_cast<stub_t<interf_t>*>(obj.get())->is_valid();
    }

    template<class interf_t>
    interf_t* release_stub(const ref_t<interf_t>& obj) {
        return const_cast<ref_t<interf_t>&>(obj).release();
    }
}