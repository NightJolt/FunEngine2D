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
        void set_color(rgba_t);

        void set_points(const std::vector <vec2f_t>&);

        void set_closed(bool);

    private:
        void update() const;

        void update_body() const;
        void update_color() const;

        void draw(sf::RenderTarget&, sf::RenderStates) const final;
        
        std::vector <vec2f_t> m_points;

        bool m_is_closed;

        float m_width;
        rgba_t m_color;

        mutable bool m_update_body;
        mutable bool m_update_color;

        mutable primitive_t m_primitive;
    };
}