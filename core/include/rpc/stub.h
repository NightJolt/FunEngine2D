#pragma once

#include "defs.h"

namespace fun::rpc {
    template <class intref_t>
    class stub_t : public intref_t {
    public:
        stub_t(fun::rpc::addr_t owner_addr, fun::rpc::oid_t owner_oid) : owner_addr(owner_addr), owner_oid(owner_oid) {}

    protected:
        fun::rpc::addr_t owner_addr;
        fun::rpc::oid_t owner_oid;
    };
}