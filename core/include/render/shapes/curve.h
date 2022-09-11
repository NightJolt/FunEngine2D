#pragma once

#include "../../globals.h"
#include "../../_math.h"
#include "../../color.h"
#include "primitive.h"

namespace fun::render::shape {
    class curve_t final : public sf::Drawable {
    public:
        curve_t();

        void set_width(float);
        void set_outline_width(float);

        void set_color(sf::Color);
        void set_outline_color(sf::Color);

        void set_points(const std::vector <vec2f_t>&);

    private:
        void update() const;

        void update_body() const;
        void update_texture() const;
        void update_color() const;

        void draw(sf::RenderTarget&, sf::RenderStates) const final;

        float m_width;
        float m_outline_width;
        rgba_t m_color;
        rgba_t m_outline_color;
        std::vector <vec2f_t> m_points;

        mutable bool m_update_body = false;
        mutable bool m_update_color = false;

        mutable primitive_t m_primitive;
    };
}