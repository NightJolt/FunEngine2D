#pragma once

#include "StaticObject.h"

namespace fun {
    class LiveObject : public StaticObject {
    public:

        LiveObject() = default;
        virtual ~LiveObject() = default;

        virtual void Update() = 0;

    private:
    };
}