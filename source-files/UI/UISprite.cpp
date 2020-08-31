#include "UI/UISprite.h"

UISprite::UISprite(sf::FloatRect r, sf::Texture* t) {
    vertex_arr = sf::VertexArray(sf::Quads, 4);

    SetSpriteRect(r);
    SetTexure(t);
    //SetColor(sf::Color::Red);
}

UISprite::~UISprite() = default;


void UISprite::SetSpriteRect(sf::FloatRect& r) {
    vertex_arr[0].position = sf::Vector2f(r.left, r.top);
    vertex_arr[1].position = sf::Vector2f(r.left + r.width, r.top);
    vertex_arr[2].position = sf::Vector2f(r.left + r.width, r.top + r.height);
    vertex_arr[3].position = sf::Vector2f(r.left, r.top + r.height);
}

void UISprite::SetTexure(sf::Texture* t) {
    texture = t;

    sf::Vector2u s = t->getSize();

    vertex_arr[0].texCoords = sf::Vector2f(0, 0);
    vertex_arr[1].texCoords = sf::Vector2f(s.x, 0);
    vertex_arr[2].texCoords = sf::Vector2f(s.x, s.y);
    vertex_arr[3].texCoords = sf::Vector2f(0, s.y);
}

void UISprite::SetColor(sf::Color c) {
    for (int i = 0; i < 4; i++) {
        vertex_arr[i].color = c;
    }
}

void UISprite::draw(sf::RenderTarget& t, sf::RenderStates s) const {
    s.texture = texture;

    t.draw(vertex_arr, s);
}

void UISprite::Rescale(sf::Vector2f s) {
    sf::Vector2f pivot;

    switch(settings.stick_to_point) {
        case UI::StickPoint::CENTER:
            pivot = vertex_arr[0].position + (vertex_arr[2].position - vertex_arr[0].position) * .5f;

            break;
        default:
            pivot = vertex_arr[settings.stick_to_point].position;

            break;
    }

    for (int i = 0; i < 4; i++) {
        vertex_arr[i].position = (vertex_arr[i].position - pivot) * s + pivot;
    }
}
