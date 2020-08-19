#pragma once

#include <SFML/Window.hpp>

#include "Math.h"

#define KEYBOARD_KEY_COUNT sf::Keyboard::Key::KeyCount
#define MOUSE_BUTTON_COUNT sf::Mouse::Button::ButtonCount
#define JOYSTICK_BUTTON_COUNT Input::JoystickButtonCount
#define JOYSTICK_AXIS_COUNT Input::JoystickAxisCount
#define MAX_JOYSTICK_COUNT 8

class Input {
public:
    static void Listen();

    static bool Pressed(sf::Keyboard::Key);
    static bool Released(sf::Keyboard::Key);
    static bool Hold(sf::Keyboard::Key);
    static int Horizontal(sf::Keyboard::Key = sf::Keyboard::Key::A, sf::Keyboard::Key = sf::Keyboard::Key::D);
    static int Vertical(sf::Keyboard::Key = sf::Keyboard::Key::S, sf::Keyboard::Key = sf::Keyboard::Key::W);
    static sf::Vector2f K2D(
            sf::Keyboard::Key = sf::Keyboard::Key::A,
            sf::Keyboard::Key = sf::Keyboard::Key::D,
            sf::Keyboard::Key = sf::Keyboard::Key::S,
            sf::Keyboard::Key = sf::Keyboard::Key::W
    );

    static bool Pressed(sf::Mouse::Button);
    static bool Released(sf::Mouse::Button);
    static bool Hold(sf::Mouse::Button);

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

    static bool IsJoystickConnected(int = 0);
    static bool Pressed(JoystickButton, int = 0);
    static bool Released(JoystickButton, int = 0);
    static bool Hold(JoystickButton, int = 0);
    static float Value(JoystickAxis, int = 0);
    static sf::Vector2f J2D(
            JoystickAxis = JoystickAxis::L3X,
            JoystickAxis = JoystickAxis::L3Y
    );

private:

    static bool keyboard_key_pressed[KEYBOARD_KEY_COUNT];
    static bool keyboard_key_released[KEYBOARD_KEY_COUNT];
    static bool keyboard_key_hold[KEYBOARD_KEY_COUNT];

    static bool mouse_button_pressed[MOUSE_BUTTON_COUNT];
    static bool mouse_button_released[MOUSE_BUTTON_COUNT];
    static bool mouse_button_hold[MOUSE_BUTTON_COUNT];

    static bool joystick_button_pressed[JOYSTICK_BUTTON_COUNT][MAX_JOYSTICK_COUNT];
    static bool joystick_button_released[JOYSTICK_BUTTON_COUNT][MAX_JOYSTICK_COUNT];
    static bool joystick_button_hold[JOYSTICK_BUTTON_COUNT][MAX_JOYSTICK_COUNT];
};