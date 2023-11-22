#pragma once

#include "defs.h"
#include "serialize.h"
#include "hollow.h"

namespace fun::rpc {
    class invoker_t {
    public:
        void invoke(deserializer_t&, i_hollow_t*, serializer_t&);
        void register_interface(iid_t, std::function<void(fun::rpc::deserializer_t&, fun::rpc::i_hollow_t*, serializer_t&)>);

    private:
        std::unordered_map<iid_t, std::function<void(fun::rpc::deserializer_t&, fun::rpc::i_hollow_t*, serializer_t&)>> invokers;
    };
}