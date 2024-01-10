#include "rpc/storage.h"

#include "rpc/scope.h"

fun::rpc::remote_storage_t::remote_storage_t(i_rpc_t& rpc, addr_t addr)
    : rpc(rpc), addr(addr) {}

fun::rpc::i_hollow_t* fun::rpc::remote_storage_t::request_unknown(iid_t iid, key_t key) {
    serializer_t serializer;

    serializer.serialize<oid_t>(call_type_t::global);
    serializer.serialize<mid_t>(request_type_t::fetch_object);
    serializer.serialize<key_t>(key);

    auto& rpc = get_rpc_scope();

    auto connection = rpc.get_connection_provider().get_connection(addr);
    
    if (!connection.is_valid()) {
        return nullptr;
    }

    connection.send(serializer.get_data(), serializer.get_size());
    
    oid_t oid = 0;
    auto sync_call_data_extractor = [&oid](deserializer_t& deserializer) {
        oid = deserializer.deserialize<oid_t>();
    };

    wait_for_sync_call_reply(sync_call_data_extractor);

    return rpc.get_stub_factory().create(iid, addr, oid);
}

void fun::rpc::local_storage_t::serialize_object(key_t key, serializer_t& serializer) {
    serializer.serialize<oid_t>(call_type_t::global);
    serializer.serialize<mid_t>(request_type_t::sync_call_reply);
    serializer.serialize<oid_t>(storage[key]);
}

void fun::rpc::local_storage_t::store_object(key_t key, i_hollow_t* oid) {
    storage[key] = (oid_t)oid;
}
