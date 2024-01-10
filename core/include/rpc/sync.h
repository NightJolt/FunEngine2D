#pragma once

#include "defs.h"
#include "connection.h"
#include "serialize.h"

namespace fun::rpc {
    void wait_for_sync_call_reply(std::function<void(deserializer_t&)>);
}