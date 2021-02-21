#pragma once

#include "UISprite.h"
#include "UIText.h"

#include "Collider.h"
#include "Input.h"

class UIButton : public UISprite, public UIText {
public:
    explicit UIButton(sf::FloatRect, std::function <void()> = [](){});
    ~UIButton() override;

    void Update(sf::RenderWindow&) override;
    void SetCallback(std::function <void()>);
    void Rescale(sf::Vector2f) override;

protected:
    void draw(sf::RenderTarget&, sf::RenderStates) const override;

    void CenterText();

    std::function <void()> callback;
};