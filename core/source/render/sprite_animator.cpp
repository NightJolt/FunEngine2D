#include "render/sprite_animator.h"
#include "render/sprite.h"

fun::render::sprite_animator_t::sprite_animator_t(sprite_t& sprite) : m_sprite(sprite) {
    reset();
}

void fun::render::sprite_animator_t::set_sequence(const std::vector <uint32_t>& sequence) {
    m_sequence = std::move(sequence);

    reset();
}

void fun::render::sprite_animator_t::set_interval(float interval) {
    m_interval = interval;
}

void fun::render::sprite_animator_t::animate(bool animate) {
    m_animate = animate;
}

void fun::render::sprite_animator_t::update(float delta) {
    if (m_animate) {
        m_cooldown -= delta;

        if (m_cooldown <= 0.0f) {
            m_cooldown = m_interval;
            m_index++;

            if (m_index >= m_sequence.size()) {
                m_index = 0;
            }

            uint32_t cur_subtexture = m_sequence[m_index];

            if (cur_subtexture != m_prev_subtexture) {
                m_sprite.select_subtexture(cur_subtexture);
                m_prev_subtexture = cur_subtexture;
            }
        }
    }
}

void fun::render::sprite_animator_t::reset() {
    m_index = 0;
    m_cooldown = m_interval;
    m_prev_subtexture = 0;

    m_sprite.select_subtexture(0);
}