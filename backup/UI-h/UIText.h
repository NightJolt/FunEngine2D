#pragma once

#include "UI.h"

class UIText : public virtual UI {
public:
    UIText(sf::Vector2f, bool = true);
    ~UIText() override;

    sf::Text text;

    void Rescale(sf::Vector2f) override;

protected:
    void draw(sf::RenderTarget&, sf::RenderStates) const override;

    void UpdateOrigin();

    bool self_origin;
};