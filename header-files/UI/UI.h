#pragma once

#include <SFML/Graphics.hpp>

#include "globals.h"

class UI : public sf::Drawable {
public:
    enum StickPoint { TOP_LEFT, TOP_RIGHT, BOTTOM_RIGHT, BOTTOM_LEFT, CENTER };

    struct Settings {
        Settings() : static_size(false), screen_space(true), stick_to_point(StickPoint::CENTER) {}

        bool static_size;
        bool screen_space;

        StickPoint stick_to_point;
    } settings;

    virtual ~UI() = 0;

    void Rescale(float);
    virtual void Rescale(sf::Vector2f);

protected:
};