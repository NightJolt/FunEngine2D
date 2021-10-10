#pragma once

#include "../globals.h"

#include "WindowManager.h"

namespace fun {
    class Drawable {
    public:

        Drawable() = default;
        virtual ~Drawable() noexcept = 0;

        virtual void Draw(WindowManager::WindowData*, int) const = 0;
    };
}