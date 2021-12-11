#pragma once

#include "Object.h"

namespace fun {
    class LiveObject : public Object {
    public:

        LiveObject() = default;
        ~LiveObject() noexcept override = 0;

        virtual void Update();

    private:
    };
}