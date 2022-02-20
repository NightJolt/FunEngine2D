#pragma once

#include "../../globals.h"
#include "../../_Math.h"

namespace fun {
    class CurvedLine final : public sf::Drawable {
    public:

        CurvedLine();
        ~CurvedLine() noexcept final = default;

        void SetPoints(sf::Vector2f, sf::Vector2f);
        void SetRadius(float);
        void SetSmoothness(int);
        void CurveAt(float);
        void SetColor(const sf::Color&);

    private:

        void Build() const;

        void draw(sf::RenderTarget&, sf::RenderStates) const final;

        sf::Vector2f from;
        sf::Vector2f to;

        float radius = 40;
        int smoothness = 5;
        float curving_point = .5f;
        sf::Color color = { 0, 0, 0 };

        mutable bool should_update = false;
        mutable std::vector <sf::Vertex> points;
    };
}