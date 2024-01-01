#include "rpc/stub.h"

fun::rpc::i_hollow_t* fun::rpc::stub_factory_t::create(iid_t iid, addr_t owner_addr, oid_t owner_oid, connection_provider_t& connection_provider) {
    if (owner_oid == 0) {
        return nullptr;
    }

    if (factories.find(iid) == factories.end()) {
        return nullptr;
    }

    return factories[iid](owner_addr, owner_oid, connection_provider);
}

void fun::rpc::stub_factory_t::register_interface(iid_t iid, std::function<i_hollow_t*(fun::rpc::addr_t, fun::rpc::oid_t, fun::rpc::connection_provider_t&)> factory) {
    factories[iid] = factory;
}
