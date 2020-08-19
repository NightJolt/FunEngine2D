#include "Input.h"



bool Input::keyboard_key_pressed[KEYBOARD_KEY_COUNT];
bool Input::keyboard_key_released[KEYBOARD_KEY_COUNT];
bool Input::keyboard_key_hold[KEYBOARD_KEY_COUNT];

bool Input::mouse_button_pressed[MOUSE_BUTTON_COUNT];
bool Input::mouse_button_released[MOUSE_BUTTON_COUNT];
bool Input::mouse_button_hold[MOUSE_BUTTON_COUNT];

bool Input::joystick_button_pressed[JOYSTICK_BUTTON_COUNT][MAX_JOYSTICK_COUNT];
bool Input::joystick_button_released[JOYSTICK_BUTTON_COUNT][MAX_JOYSTICK_COUNT];
bool Input::joystick_button_hold[JOYSTICK_BUTTON_COUNT][MAX_JOYSTICK_COUNT];



void Input::Listen() {
    for (int key = 0; key < KEYBOARD_KEY_COUNT; key++) {
        if (sf::Keyboard::isKeyPressed(static_cast <sf::Keyboard::Key> (key))) {
            if (keyboard_key_hold[key]) {
                keyboard_key_pressed[key] = false;
            } else {
                keyboard_key_pressed[key] = true;
                keyboard_key_hold[key] = true;
            }
        } else {
            if (keyboard_key_hold[key]) {
                keyboard_key_pressed[key] = false;
                keyboard_key_hold[key] = false;
                keyboard_key_released[key] = true;
            } else if (keyboard_key_released[key]) {
                keyboard_key_released[key] = false;
            }
        }
    }

    for (int button = 0; button < MOUSE_BUTTON_COUNT; button++) {
        if (sf::Mouse::isButtonPressed(static_cast <sf::Mouse::Button> (button))) {
            if (mouse_button_hold[button]) {
                mouse_button_pressed[button] = false;
            } else {
                mouse_button_pressed[button] = true;
                mouse_button_hold[button] = true;
            }
        } else {
            if (mouse_button_hold[button]) {
                mouse_button_pressed[button] = false;
                mouse_button_hold[button] = false;
                mouse_button_released[button] = true;
            } else if (mouse_button_released[button]) {
                mouse_button_released[button] = false;
            }
        }
    }

    for (int button = 0; button < JOYSTICK_BUTTON_COUNT; button++) {
        for (int index = 0; index < MAX_JOYSTICK_COUNT; index++) {
            if (IsJoystickConnected(index)) {
                if (sf::Joystick::isButtonPressed(index, button)) {
                    if (joystick_button_hold[button][index]) {
                        joystick_button_pressed[button][index] = false;
                    } else {
                        joystick_button_pressed[button][index] = true;
                        joystick_button_hold[button][index] = true;
                    }
                } else {
                    if (joystick_button_hold[button][index]) {
                        joystick_button_pressed[button][index] = false;
                        joystick_button_hold[button][index] = false;
                        joystick_button_released[button][index] = true;
                    } else if (joystick_button_released[button][index]) {
                        joystick_button_released[button][index] = false;
                    }
                }
            } else {
                joystick_button_pressed[button][index] = false;
                joystick_button_hold[button][index] = false;
                joystick_button_released[button][index] = false;
            }
        }
    }
}



bool Input::Pressed(sf::Keyboard::Key key) {
    return keyboard_key_pressed[key];
}

bool Input::Released(sf::Keyboard::Key key) {
    return keyboard_key_released[key];
}

bool Input::Hold(sf::Keyboard::Key key) {
    return keyboard_key_hold[key];
}

int Input::Horizontal(sf::Keyboard::Key a, sf::Keyboard::Key b) {
    return keyboard_key_hold[b] - keyboard_key_hold[a];
}

int Input::Vertical(sf::Keyboard::Key a, sf::Keyboard::Key b) {
    return keyboard_key_hold[b] - keyboard_key_hold[a];
}

sf::Vector2f Input::K2D(sf::Keyboard::Key a, sf::Keyboard::Key b, sf::Keyboard::Key c, sf::Keyboard::Key d) {
    return Math::Normalize(sf::Vector2f(Horizontal(a, b), Vertical(c, d)));
}



bool Input::Pressed(sf::Mouse::Button button) {
    return mouse_button_pressed[button];
}

bool Input::Released(sf::Mouse::Button button) {
    return mouse_button_released[button];
}

bool Input::Hold(sf::Mouse::Button button) {
    return mouse_button_hold[button];
}



bool Input::IsJoystickConnected(int index) {
    return sf::Joystick::isConnected(index);
}

bool Input::Pressed(JoystickButton button, int index) {
    return joystick_button_pressed[button][index];
}

bool Input::Released(JoystickButton button, int index) {
    return joystick_button_released[button][index];
}

bool Input::Hold(JoystickButton button, int index) {
    return joystick_button_hold[button][index];
}

float Input::Value(JoystickAxis axis, int index) {
    auto jaxis = static_cast <sf::Joystick::Axis> (axis);

    if (IsJoystickConnected(index) && sf::Joystick::hasAxis(index, jaxis)) {
        float value = sf::Joystick::getAxisPosition(index, jaxis);

        if (axis == L2 || axis == R2) value = (value + 100) / 2;

        return value / 100;

    } else {
        return 0;
    }
}

sf::Vector2f Input::J2D(Input::JoystickAxis a, Input::JoystickAxis b) {
    return Math::Normalize(sf::Vector2f(Value(a), Value(b)));
}