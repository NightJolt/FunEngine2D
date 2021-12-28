#pragma once

#include "../../../core/include/globals.h"

namespace fun {
    class Entity {
    public:

        Entity() = default;
        virtual ~Entity() noexcept = 0;

        virtual void Init();
        virtual void Dispose();

        bool active = false;
        bool alive = false;
        bool should_be_disposed = false; // ! REMOVE
        std::string name = "";
        uint64_t uuid = 0;

    private:
    };
}