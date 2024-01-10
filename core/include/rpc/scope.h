#pragma once

#include "defs.h"
#include "interfaces.h"

namespace fun::rpc {
    void set_rpc_scope(i_rpc_t&);
    void unset_rpc_scope();
    i_rpc_t& get_rpc_scope();

    struct rpc_scope_lock_t {
        rpc_scope_lock_t(i_rpc_t& rpc);
        ~rpc_scope_lock_t();
    };
}
