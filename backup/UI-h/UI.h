#pragma once

#include <SFML/Graphics.hpp>

#include "globals.h"

class UI : public sf::Drawable {
public:
    enum StickPoint { TOP_LEFT, TOP_RIGHT, BOTTOM_RIGHT, BOTTOM_LEFT, CENTER };
    enum State { IDLE, HOVERED, PRESSED };

    struct Settings {
        Settings() : static_size(false), screen_space(true), stick_to_point(StickPoint::CENTER), state(State::IDLE) {
            for (auto& color : colors) {
                color = sf::Color::White;
            }
        }

        bool static_size;
        bool screen_space;

        sf::Color colors[3];

        State state;
        StickPoint stick_to_point;
    } settings;

    virtual ~UI() = 0;

    virtual void Update(sf::RenderWindow&);

    virtual void Rescale(sf::Vector2f);

protected:
};