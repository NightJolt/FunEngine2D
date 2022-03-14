#pragma once

#include "globals.h"
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

    struct transform_t {
        vec2f_t position;
        float rotation;

        explicit transform_t(vec2f_t = { 0, 0 }, float = 0);
    };
}