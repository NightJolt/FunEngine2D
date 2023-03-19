#pragma once

#include "../globals.h"
#include "../vec2.h"
#include "../transform.h"
#include "../color.h"
#include "shapes/primitive.h"
#include "texture.h"

namespace fun::render {
    class sprite_t : public sf::Drawable {
    public:
        enum draw_mode_t {
            normal,
            nineslice
        };

        sprite_t();

        void bind_texture(const texture_t&);
        void bind_shader(sf::Shader*);

        void select_subtexture(uint32_t);
        void select_subtexture(vec2u_t);
        void select_subtexture(vec2u_t, vec2u_t);

        vec2f_t get_position() const;
        void set_position(vec2f_t);
        void move(vec2f_t);

        float32_t get_rotation() const;
        void set_rotation(float32_t);
        void rotate(float32_t);

        vec2f_t get_scale() const;
        void set_scale(vec2f_t);
        void scale(float32_t);
        void scale(vec2f_t);

        void set_origin(vec2f_t);
        void set_color(rgba_t);

        void set_draw_mode(draw_mode_t);
        void set_nineslice(float32_t4, float32_t);

        void batch(sprite_t*, sprite_t*);

        void update() const;

    private:
        void update_body() const;
        void update_texture() const;
        void update_color() const;

        void draw(sf::RenderTarget&, sf::RenderStates) const override;

        mutable primitive_t m_primitive;

        transform_t m_transform;
        vec2f_t m_origin;
        rgba_t m_color;
        vec2u_t m_texture_pos;
        vec2u_t m_texture_size;

        draw_mode_t m_draw_mode;
        float32_t4 m_nineslice; // left, top, right, bottom
        float32_t m_nineslice_scale;

        texture_t m_texture;
        sf::Shader* m_shader;

        mutable bool m_update_body;
        mutable bool m_update_texture;
        mutable bool m_update_color;

        static constexpr uint32_t s_nineslice_vertex_count = 24;
        static constexpr uint32_t s_nineslice_vertex_order[s_nineslice_vertex_count] = { 0, 4, 1, 5, 2, 6, 3, 7, 7, 11, 6, 10, 5, 9, 4, 8, 8, 12, 9, 13, 10, 14, 11, 15 };
    };
}