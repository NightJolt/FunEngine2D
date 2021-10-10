#pragma once

#include "../../../core/include/globals.h"

#include "../../../core/include/Math.h"

namespace fun {
    class CurvedLine : public sf::Drawable {
    public:

        CurvedLine();

        void SetPoints(sf::Vector2f, sf::Vector2f, bool = true);
        void SetRadius(float, bool = true);
        void SetSmoothness(int, bool = true);
        void CurveAt(float, bool = true);
        void SetColor(sf::Color, bool = true);

    private:

        sf::Vector2f from;
        sf::Vector2f to;

        float radius = 40;
        int smoothness = 5;
        float curving_point = .5f;

        sf::Color color;

        std::vector<sf::Vertex> points;

        void Build();

        void draw(sf::RenderTarget &, sf::RenderStates) const override;
    };
}