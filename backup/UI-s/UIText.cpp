#include "UI/UIText.h"

UIText::UIText(sf::Vector2f p, bool so) : self_origin(so) {
    UpdateOrigin();

    text.setPosition(p);
}

UIText::~UIText() = default;

void UIText::Rescale(sf::Vector2f s) {
    UpdateOrigin();

    text.scale(s);
}

void UIText::draw(sf::RenderTarget& rt, sf::RenderStates rs) const {
    if (text.getString() != "") rt.draw(text, rs);
}

void UIText::UpdateOrigin() {
    if (!self_origin) return;

    switch (settings.stick_to_point) {
        case UI::StickPoint::CENTER:
            text.setOrigin(text.getScale() * .5f);

            break;
        case UI::StickPoint::TOP_LEFT:
            text.setOrigin(sf::Vector2f(0, 0));

            break;
        case UI::StickPoint::TOP_RIGHT:
            text.setOrigin(text.getScale() * sf::Vector2f(1, 0));

            break;
        case UI::StickPoint::BOTTOM_RIGHT:
            text.setOrigin(text.getScale() * sf::Vector2f(1, 1));

            break;
        case UI::StickPoint::BOTTOM_LEFT:
            text.setOrigin(text.getScale() * sf::Vector2f(0, 1));

            break;
    }
}