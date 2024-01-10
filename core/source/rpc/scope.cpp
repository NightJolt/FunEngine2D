#include "rpc/scope.h"

namespace {
    struct rpc_scope_info_t {
        fun::rpc::i_rpc_t* scope = nullptr;
        int32_t depth = 0;
    };

    std::map<size_t, rpc_scope_info_t> per_thread_rpc_scope_infos;

    rpc_scope_info_t& get_rpc_scope_info() {
        auto& info = per_thread_rpc_scope_infos[std::hash<std::thread::id>{}(std::this_thread::get_id())];

        return info;
    }
}

void fun::rpc::set_rpc_scope(i_rpc_t& rpc) {
    auto& rpc_info = ::get_rpc_scope_info();

    assert(rpc_info.depth == 0 || rpc_info.scope == &rpc);

    rpc_info.scope = &rpc;
    rpc_info.depth++;
    
}

void fun::rpc::unset_rpc_scope() {
    auto& rpc_info = ::get_rpc_scope_info();

    assert(rpc_info.depth > 0);

    rpc_info.depth--;

    if (rpc_info.depth == 0) {
        rpc_info.scope = nullptr;
    }
}

fun::rpc::i_rpc_t& fun::rpc::get_rpc_scope() {
    return *::get_rpc_scope_info().scope;
}

fun::rpc::rpc_scope_lock_t::rpc_scope_lock_t(i_rpc_t& rpc) {
    set_rpc_scope(rpc);
}

fun::rpc::rpc_scope_lock_t::~rpc_scope_lock_t() {
    unset_rpc_scope();
}
