#pragma once

#include "defs.h"
#include "serialize.h"
#include "hollow.h"

namespace fun::rpc {
    class invoker_t : public i_invoker_t {
    public:
        void invoke(deserializer_t&, i_hollow_t*, serializer_t&) override;
        void register_interface(iid_t, invoker_fn_t) override;

    private:
        std::unordered_map<iid_t, invoker_fn_t> invokers;
    };
}