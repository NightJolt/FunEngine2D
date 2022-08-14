#pragma once

#include "../globals.h"
#include "../vec2.h"
#include "../transform.h"
#include "../color.h"
#include "../_math.h"
#include "shapes/primitive.h"
#include "../tools/debugger.h"
#include "texture.h"

namespace fun {
    class sprite_t : public sf::Drawable {
    public:
        sprite_t();

        void bind_texture(const texture_t&);
        void bind_shader(sf::Shader*);

        void select_subtexture(uint32_t);
        void select_subtexture(vec2u_t);
        void select_subtexture(vec2u_t, vec2u_t);

        void set_position(vec2f_t);
        void move(vec2f_t);

        void set_rotation(float);
        void rotate(float);

        void set_scale(vec2f_t);
        void scale(float);
        void scale(vec2f_t);

        void set_origin(vec2f_t);
        void set_color(rgba_t);

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

        texture_t m_texture;
        sf::Shader* m_shader;

        mutable bool m_update_body;
        mutable bool m_update_texture;
        mutable bool m_update_color;
    };
}