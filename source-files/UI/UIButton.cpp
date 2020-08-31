#include "UI/UIButton.h"

UIButton::UIButton(sf::FloatRect r, std::function <void()> f) : UISprite(r, nullptr), UIText((vertex_arr[0].position + vertex_arr[2].position) * .5f, false), callback(std::move(f)) {
    CenterText();
}

UIButton::~UIButton() = default;

void UIButton::Update(sf::RenderWindow& window) {
    settings.state = State::IDLE;

    sf::Vector2f size = vertex_arr[2].position - vertex_arr[0].position;
    bool hovered = Collider::PointVsRect((sf::Vector2f)sf::Mouse::getPosition(window), Collider::Rect(vertex_arr[0].position + size * .5f, size));
    if (hovered) settings.state = State::HOVERED;

    if (Input::Hold(sf::Mouse::Left) && hovered) settings.state = State::PRESSED;
    if (Input::Pressed(sf::Mouse::Left) && hovered) callback();

    for (int i = 0; i < 4; i++) {
        vertex_arr[i].color = settings.colors[settings.state];
    }

    sf::FloatRect text_bounds = text.getLocalBounds();
    text.setOrigin(sf::Vector2(text_bounds.width * .5f, text_bounds.height));
}

void UIButton::SetCallback(std::function <void()> f) {
    callback = move(f);
}

void UIButton::Rescale(sf::Vector2f s) {
    UISprite::Rescale(s);
    UIText::Rescale(s);

    CenterText();
}

void UIButton::CenterText() {
    text.setPosition((vertex_arr[0].position + vertex_arr[2].position) * .5f);
}

void UIButton::draw(sf::RenderTarget& rt, sf::RenderStates rs) const {
    UISprite::draw(rt, rs);
    UIText::draw(rt, rs);
}