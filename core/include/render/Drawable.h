#pragma once

#include "../globals.h"

#include "WindowManager.h"

namespace fun {
    class Drawable {
    public:

        Drawable() = default;
        virtual ~Drawable() noexcept = 0;

        virtual void Draw(wndmgr::Window*) const = 0;

        void Drawable_SetDrawingLayer(uint32_t);
        uint32_t Drawable_GetDrawingLayer() const;

    private:

        uint32_t layer = 0;
    };
}