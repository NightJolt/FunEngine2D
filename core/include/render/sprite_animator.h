#pragma once

#include "../globals.h"
#include "sprite.h"

namespace fun {
    class sprite_animator_t {
    public:
        sprite_animator_t(sprite_t&);

        void set_sequence(const std::vector <uint32_t>&);
        void set_interval(float);

        void animate(bool);
        void update(float);

        void reset();

    private:
        sprite_t& m_sprite;
        std::vector <uint32_t> m_sequence;
        float m_interval;
        float m_index;
        float m_cooldown;
        bool m_animate;
        uint32_t m_prev_subtexture;
    };
}