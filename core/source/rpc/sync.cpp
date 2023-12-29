#include "rpc/sync.h"

void fun::rpc::wait_for_sync_call_reply(connection_provider_t& connection_provider, std::function<void(deserializer_t&)> sync_call_data_extractor) {
    uint32_t packet_ind = 0;
    auto& packet_storage = connection_provider.get_packet_storage();

    while (true) {
        connection_provider.check_for_incoming_connections();
        connection_provider.check_for_incoming_data();
        
        while (packet_ind < packet_storage.get_size()) {
            auto& packet = packet_storage[packet_ind];
            deserializer_t deserializer(packet.get_data());

            oid_t call_type = deserializer.deserialize<oid_t>();

            if (call_type == call_type_t::global) {
                mid_t request_type = deserializer.deserialize<mid_t>();

                if (request_type == request_type_t::sync_call_reply) {
                    sync_call_data_extractor(deserializer);

                    packet_storage.remove(packet_ind);

                    return;
                }
            }

            packet_ind++;
        }
    }
}
