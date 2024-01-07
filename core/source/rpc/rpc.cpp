#include "rpc/rpc.h"

void fun::rpc::rpc_t::init(port_t port) {
    connection_provider.init(port);
}

void fun::rpc::rpc_t::quit() {
    connection_provider.quit();
}

void fun::rpc::rpc_t::step() {
    process_connections();
    process_packets();
}

void fun::rpc::rpc_t::run() {
    while (true) {
        step();
    }
}

fun::rpc::connection_provider_t& fun::rpc::rpc_t::get_connection_provider() {
    return connection_provider;
}

fun::rpc::stub_factory_t& fun::rpc::rpc_t::get_stub_factory() {
    return stub_factory;
}

fun::rpc::remote_storage_t fun::rpc::rpc_t::get_remote_storage(addr_t addr) {
    return remote_storage_t(addr, connection_provider, stub_factory);
}

fun::rpc::local_storage_t& fun::rpc::rpc_t::get_local_storage() {
    return local_storage;
}

fun::rpc::invoker_t& fun::rpc::rpc_t::get_invoker() {
    return invoker;
}

void fun::rpc::rpc_t::process_connections() {
    connection_provider.check_for_incoming_connections();
    connection_provider.check_for_incoming_data();
}

void fun::rpc::rpc_t::process_packet(packet_t& packet) {
    deserializer_t deserializer(packet.get_data(), connection_provider, stub_factory);

    oid_t oid = deserializer.deserialize<oid_t>();

    if (oid == call_type_t::global) {
        mid_t request_type = deserializer.deserialize<mid_t>();

        if (request_type == request_type_t::fetch_object) {
            key_t key = deserializer.deserialize<key_t>();

            serializer_t serializer;
            local_storage.serialize_object(key, serializer);
            
            auto connection = connection_provider.get_connection(packet.get_sender_addr());
            if (connection.is_valid()) {
                connection.send(serializer.get_data(), serializer.get_size());
            }
        } else if (request_type == request_type_t::sync_call_reply) {
            return; // ? sync call replys should not be processed here
        }
    } else {
        i_hollow_t* hollow = object_storage.fetch(oid);
        serializer_t serializer;

        invoker.invoke(deserializer, hollow, serializer);

        if (serializer.get_size() > 0) {
            auto connection = connection_provider.get_connection(packet.get_sender_addr());

            if (connection.is_valid()) {
                connection.send(serializer.get_data(), serializer.get_size());
            }
        }
    }
}

void fun::rpc::rpc_t::process_packets() {
    auto& packets = connection_provider.get_packet_storage();

    while (!packets.empty()) {
        auto packet = packets.pop();

        process_packet(packet);
    }
}
