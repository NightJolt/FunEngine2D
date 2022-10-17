#pragma once

#include "../../globals.h"
#include "vec2.h"

namespace fun::render {
    class rounded_rect_t final : public sf::Drawable {
    public:
        rounded_rect_t();
        ~rounded_rect_t() noexcept final = default;

        void set_raidus(float);
        void set_position(vec2f_t);
        vec2f_t get_position() const;
        void set_size(vec2f_t);
        vec2f_t get_size() const;
        void set_smoothness(int);
        void set_fill_color(sf::Color);

    private:
        void build() const;

        void draw(sf::RenderTarget&, sf::RenderStates) const final;

        float radius = 10;
        int smoothness = 5;
        vec2f_t position = { 0, 0 };
        vec2f_t size = { 200, 100 };
        sf::Color color = { 150, 150, 150 };

        mutable bool should_update = false;
        mutable std::vector <sf::Vertex> points;
    };
}