#pragma once

#include "../../../core/include/globals.h"

#include "../../../core/include/_Math.h"

namespace fun {
    class RoundedRect final : public sf::Drawable {
    public:

        RoundedRect();
        ~RoundedRect() noexcept final = default;

        void SetRadius(float);
        void SetPosition(const sf::Vector2f&);
        const sf::Vector2f& GetPosition();
        void SetSize(const sf::Vector2f&);
        const sf::Vector2f& GetSize();
        void SetSmoothness(int);
        void SetFillColor(const sf::Color&);

    private:

        void Build() const;

        void draw(sf::RenderTarget&, sf::RenderStates) const final;

        float radius = 10;
        int smoothness = 5;
        sf::Vector2f position = { 0, 0 };
        sf::Vector2f size = { 200, 100 };
        sf::Color color = { 150, 150, 150 };

        mutable bool should_update = false;
        mutable std::vector <sf::Vertex> points;
    };
}