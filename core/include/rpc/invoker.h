#pragma once

#include "defs.h"
#include "serialize.h"
#include "hollow.h"

namespace fun::rpc {
    class invoker_t {
    public:
        void invoke(deserializer_t& deserializer, i_hollow_t* object, serializer_t& serializer) {
            iid_t iid = deserializer.deserialize<iid_t>();

            invokers[iid](deserializer, object, serializer);
        }

        void register_interface(iid_t iid, std::function<void(fun::rpc::deserializer_t&, fun::rpc::i_hollow_t*, serializer_t&)> invoker) {
            invokers[iid] = invoker;
        }

    private:
        std::unordered_map<iid_t, std::function<void(fun::rpc::deserializer_t&, fun::rpc::i_hollow_t*, serializer_t&)>> invokers;
    };
}