#include "rpc/storage.h"

fun::rpc::remote_storage_t::remote_storage_t(addr_t addr, connection_provider_t& connection_provider, stub_factory_t& stub_factory)
    : addr(addr), connection_provider(connection_provider), stub_factory(stub_factory) {}

fun::rpc::i_hollow_t* fun::rpc::remote_storage_t::request_unknown(iid_t iid, key_t key) {
    serializer_t serializer;

    serializer.serialize<oid_t>(call_type_t::global);
    serializer.serialize<mid_t>(request_type_t::fetch_object);
    serializer.serialize<key_t>(key);

    auto connection = connection_provider.get_connection(addr);
    
    if (connection.is_valid()) {
        connection.send(serializer.get_data(), serializer.get_size());
    }
    
    oid_t oid = 0;
    auto sync_call_data_extractor = [&oid](deserializer_t& deserializer) {
        oid = deserializer.deserialize<oid_t>();
    };

    wait_for_sync_call_reply(connection_provider, sync_call_data_extractor);

    return stub_factory.create(iid, addr, oid, connection_provider);
}

void fun::rpc::local_storage_t::serialize_object(key_t key, serializer_t& serializer) {
    serializer.serialize<oid_t>(call_type_t::global);
    serializer.serialize<mid_t>(request_type_t::sync_call_reply);
    serializer.serialize<oid_t>(storage[key]);
}

void fun::rpc::local_storage_t::store_object(key_t key, i_hollow_t* oid) {
    storage[key] = (oid_t)oid;
}

void fun::rpc::object_storage_t::store(oid_t oid, i_hollow_t* object) {
    objects[oid] = object;
}

fun::rpc::i_hollow_t* fun::rpc::object_storage_t::fetch(oid_t oid) {
    return objects[oid];
}
