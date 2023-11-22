#include "rpc/invoker.h"

void fun::rpc::invoker_t::invoke(deserializer_t& deserializer, i_hollow_t* object, serializer_t& serializer) {
    iid_t iid = deserializer.deserialize<iid_t>();

    invokers[iid](deserializer, object, serializer);
}

void fun::rpc::invoker_t::register_interface(iid_t iid, std::function<void(fun::rpc::deserializer_t&, fun::rpc::i_hollow_t*, serializer_t&)> invoker) {
    invokers[iid] = invoker;
}
