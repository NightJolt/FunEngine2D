#pragma once

#include "../../globals.h"
#include "../../vec2.h"

namespace fun::render {
    class curved_line_t final : public sf::Drawable {
    public:

        curved_line_t();
        ~curved_line_t() noexcept final = default;

        void set_points(vec2f_t, vec2f_t);
        void set_radius(float);
        void set_smoothness(int);
        void curve_at(float);
        void set_color(sf::Color);

    private:

        void build() const;

        void draw(sf::RenderTarget&, sf::RenderStates) const final;

        vec2f_t from;
        vec2f_t to;

        float radius = 40;
        int smoothness = 5;
        float curving_point = .5f;
        sf::Color color = { 0, 0, 0 };

        mutable bool should_update = false;
        mutable std::vector <sf::Vertex> points;
    };
}