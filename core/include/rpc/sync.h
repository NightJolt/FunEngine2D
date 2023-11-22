#pragma once

#include "defs.h"
#include "connection.h"
#include "serialize.h"

namespace fun::rpc {
    void wait_for_sync_call_reply(connection_provider_t& connection_provider, std::function<void(deserializer_t&)> sync_call_data_extractor);
}