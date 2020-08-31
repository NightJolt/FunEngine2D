#include "UI/UI.h"

UI::~UI() = default;

void UI::Rescale(float s) {
    Rescale(sf::Vector2f(s, s));
}

void UI::Rescale(sf::Vector2f) {}