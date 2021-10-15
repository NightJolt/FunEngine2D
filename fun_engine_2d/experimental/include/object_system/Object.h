#pragma once

#include "../../../core/include/globals.h"

namespace fun {
    class Object {
    public:

        Object() = default;
        virtual ~Object() noexcept = 0;

        virtual void Init();
        virtual void Dispose();

        bool should_be_disposed = false;

    private:
    };
}