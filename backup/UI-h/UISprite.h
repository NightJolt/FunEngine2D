#pragma once

#include "UI.h"

class UISprite : public virtual UI {
public:
    explicit UISprite(sf::FloatRect, sf::Texture*);
    ~UISprite() override;

    void SetSpriteRect(sf::FloatRect&);
    void SetTexure(sf::Texture*);
    void SetColor(sf::Color);

    void Rescale(sf::Vector2f) override;

protected:
    void draw(sf::RenderTarget&, sf::RenderStates) const override;

    sf::VertexArray vertex_arr;
    sf::Texture* texture;
};