#pragma once

#include "Globals.h"
#include "vec2.h"

namespace fun {
    // struct Transform {
    //     Vec2f position;
    //     float rotation;
    //     Vec2f scale;

    //     explicit Transform(Vec2f p = { 0, 0 }, float r = 0, Vec2f s = { 1, 1 }) {
    //         position = p;
    //         rotation = r;
    //         scale = s;
    //     }
    // };

    struct Transform {
        vec2f_t position;
        float rotation;

        explicit Transform(vec2f_t = { 0, 0 }, float = 0);
    };
}