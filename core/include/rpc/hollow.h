#pragma once

#include "defs.h"

namespace fun::rpc {
    struct i_hollow_t {
        static const iid_t iid = 1;

        // virtual i_hollow_t* validate_interface(iid_t) = 0;
    };
}