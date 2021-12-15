#pragma once

#include "../globals.h"

#include "WindowManager.h"

namespace fun {
    class Drawable {
    public:

        Drawable() = default;
        virtual ~Drawable() noexcept = 0;

        virtual void Draw(wndmgr::WindowData*) const = 0;

        void Drawable_SetDrawingLayer(i32);
        i32 Drawable_GetDrawingLayer() const;

    private:

        i32 layer = 0;
    };
}