#include "rpc/invoker.h"

void fun::rpc::invoker_t::invoke(deserializer_t& deserializer, i_hollow_t* object, serializer_t& serializer) {
    iid_t iid = deserializer.deserialize<iid_t>();

    invokers[iid](deserializer, object, serializer);
}

void fun::rpc::invoker_t::register_interface(iid_t iid, invoker_fn_t invoker) {
    invokers[iid] = invoker;
}
