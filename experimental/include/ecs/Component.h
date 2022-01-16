#pragma once

#include "../../../core/include/globals.h"

namespace fun {
    class Component {
        public:

            Component();
            virtual ~Component() = 0;

            virtual void Update() = 0;

        private:

            uint64_t uuid = 0;
    };
}