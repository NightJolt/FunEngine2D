#pragma once

#include "Globals.h"
#include "_Math.h"

#define ENABLE_MOUSE
#define ENABLE_KEYBOARD
#define ENABLE_JOYSTICKS

#define KEYBOARD_KEY_COUNT sf::Keyboard::Key::KeyCount
#define MOUSE_BUTTON_COUNT sf::Mouse::Button::ButtonCount
#define JOYSTICK_BUTTON_COUNT fun::input::JoystickButtonCount
#define JOYSTICK_AXIS_COUNT fun::input::JoystickAxisCount
#define MAX_JOYSTICK_COUNT 8

namespace fun::input {
    void listen();

#if defined(ENABLE_MOUSE)
    bool pressed(sf::Mouse::Button);
    bool released(sf::Mouse::Button);
    bool hold(sf::Mouse::Button);
    sf::Vector2f mouse_2d();
#endif

#if defined(ENABLE_KEYBOARD)
    bool pressed(sf::Keyboard::Key);
    bool released(sf::Keyboard::Key);
    bool hold(sf::Keyboard::Key);
    int horizontal(sf::Keyboard::Key = sf::Keyboard::Key::A, sf::Keyboard::Key = sf::Keyboard::Key::D);
    int vertical(sf::Keyboard::Key = sf::Keyboard::Key::S, sf::Keyboard::Key = sf::Keyboard::Key::W);
    sf::Vector2f keyboard_2d(
            sf::Keyboard::Key = sf::Keyboard::Key::A,
            sf::Keyboard::Key = sf::Keyboard::Key::D,
            sf::Keyboard::Key = sf::Keyboard::Key::S,
            sf::Keyboard::Key = sf::Keyboard::Key::W
    );
#endif

#if defined(ENABLE_JOYSTICKS)
    enum JoystickButton {
        X,
        O,
        T,
        R,
        L1,
        R1,
        L2I,
        R2I,

        JoystickButtonCount
    };

    enum JoystickAxis {
        L3X,
        L3Y,
        L2,
        R2,
        R3X,
        R3Y,
        DX,
        DY,

        JoystickAxisCount
    };

    bool is_joystick_connected(int = 0);
    bool pressed(JoystickButton, int = 0);
    bool released(JoystickButton, int = 0);
    bool hold(JoystickButton, int = 0);
    float value(JoystickAxis, int = 0);
    sf::Vector2f joystick_2d(
            JoystickAxis = JoystickAxis::L3X,
            JoystickAxis = JoystickAxis::L3Y
    );
#endif
}