#pragma once

#include "Object.h"

namespace fun {
    class StaticObject : public Object {
    public:

        StaticObject() = default;
        ~StaticObject() noexcept override = 0;

    private:
    };
}