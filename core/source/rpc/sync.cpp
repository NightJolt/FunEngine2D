#include "rpc/sync.h"

void fun::rpc::wait_for_sync_call_reply(connection_provider_t& connection_provider, std::function<void(deserializer_t&)> sync_call_data_extractor) {
    uint32_t packed_ind = 0;
    auto& packet_storage = connection_provider.get_packet_storage();

    while (true) {
        connection_provider.check_for_incoming_connections();
        connection_provider.check_for_incoming_data();
        
        while (packed_ind < packet_storage.get_size()) {
            auto& packet = packet_storage[packed_ind];
            deserializer_t deserializer(packet.get_data());

            oid_t call_type = deserializer.deserialize<oid_t>();

            if (call_type == 0) {
                mid_t answer_type = deserializer.deserialize<mid_t>();

                if (answer_type == 1) {
                    sync_call_data_extractor(deserializer);

                    packet_storage.remove(packed_ind);

                    return;
                }
            }

            packed_ind++;
        }
    }
}
