#pragma once

#include "defs.h"

namespace fun::rpc {
    struct i_hollow_t {
        virtual ~i_hollow_t() = default;

        static const iid_t iid;
    };
}