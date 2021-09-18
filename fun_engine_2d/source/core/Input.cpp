#include "../../include/core/Input.h"

#if defined(ENABLE_MOUSE)
bool fun::Input::mouse_button_pressed[MOUSE_BUTTON_COUNT];
bool fun::Input::mouse_button_released[MOUSE_BUTTON_COUNT];
bool fun::Input::mouse_button_hold[MOUSE_BUTTON_COUNT];

sf::Vector2f fun::Input::mouse_position = sf::Vector2f(0, 0);
sf::Vector2f fun::Input::mouse_delta = sf::Vector2f(0, 0);
#endif

#if defined(ENABLE_KEYBOARD)
bool fun::Input::keyboard_key_pressed[KEYBOARD_KEY_COUNT];
bool fun::Input::keyboard_key_released[KEYBOARD_KEY_COUNT];
bool fun::Input::keyboard_key_hold[KEYBOARD_KEY_COUNT];
int fun::Input::last_keyboard_key_pressed = 0;
#endif

#if defined(ENABLE_JOYSTICKS)
bool fun::Input::joystick_button_pressed[JOYSTICK_BUTTON_COUNT][MAX_JOYSTICK_COUNT];
bool fun::Input::joystick_button_released[JOYSTICK_BUTTON_COUNT][MAX_JOYSTICK_COUNT];
bool fun::Input::joystick_button_hold[JOYSTICK_BUTTON_COUNT][MAX_JOYSTICK_COUNT];
#endif

void fun::Input::Listen() {
#if defined(ENABLE_MOUSE)
    for (int button = 0; button < MOUSE_BUTTON_COUNT; button++) {
        mouse_button_pressed[button] = false;
        mouse_button_released[button] = false;

        if (sf::Mouse::isButtonPressed(static_cast <sf::Mouse::Button> (button))) {
            if (!mouse_button_hold[button]) {
                mouse_button_pressed[button] = true;
                mouse_button_hold[button] = true;
            }
        } else {
            if (mouse_button_hold[button]) {
                mouse_button_hold[button] = false;
                mouse_button_released[button] = true;
            }
        }
    }

    mouse_delta = (sf::Vector2f)sf::Mouse::getPosition() - mouse_position;
    mouse_position += mouse_delta;
#endif

#if defined(ENABLE_KEYBOARD)
    for (int key = 0; key < KEYBOARD_KEY_COUNT; key++) {
        keyboard_key_pressed[key] = false;
        keyboard_key_released[key] = false;

        if (sf::Keyboard::isKeyPressed(static_cast <sf::Keyboard::Key> (key))) {
            if (!keyboard_key_hold[key]) {
                keyboard_key_pressed[key] = true;
                keyboard_key_hold[key] = true;

                last_keyboard_key_pressed = key;
            }
        } else {
            if (keyboard_key_hold[key]) {
                keyboard_key_hold[key] = false;
                keyboard_key_released[key] = true;
            }
        }
    }
#endif

#if defined(ENABLE_JOYSTICKS)
    for (int button = 0; button < JOYSTICK_BUTTON_COUNT; button++) {
        for (int index = 0; index < MAX_JOYSTICK_COUNT; index++) {
            joystick_button_pressed[button][index] = false;
            joystick_button_released[button][index] = false;

            if (IsJoystickConnected(index)) {
                if (sf::Joystick::isButtonPressed(index, button)) {
                    if (joystick_button_hold[button][index]) {
                        joystick_button_pressed[button][index] = true;
                        joystick_button_hold[button][index] = true;
                    }
                } else {
                    if (joystick_button_hold[button][index]) {
                        joystick_button_hold[button][index] = false;
                        joystick_button_released[button][index] = true;
                    }
                }
            }
        }
    }
#endif
}



#if defined(ENABLE_MOUSE)
bool fun::Input::Pressed(sf::Mouse::Button button) {
    return mouse_button_pressed[button];
}

bool fun::Input::Released(sf::Mouse::Button button) {
    return mouse_button_released[button];
}

bool fun::Input::Hold(sf::Mouse::Button button) {
    return mouse_button_hold[button];
}

sf::Vector2f fun::Input::M2D() {
    return mouse_delta;
}
#endif



#if defined(ENABLE_KEYBOARD)
bool fun::Input::Pressed(sf::Keyboard::Key key) {
    return keyboard_key_pressed[key];
}

bool fun::Input::Released(sf::Keyboard::Key key) {
    return keyboard_key_released[key];
}

bool fun::Input::Hold(sf::Keyboard::Key key) {
    return keyboard_key_hold[key];
}

int fun::Input::Horizontal(sf::Keyboard::Key a, sf::Keyboard::Key b) {
    return keyboard_key_hold[b] - keyboard_key_hold[a];
}

int fun::Input::Vertical(sf::Keyboard::Key a, sf::Keyboard::Key b) {
    return keyboard_key_hold[b] - keyboard_key_hold[a];
}

sf::Vector2f fun::Input::K2D(sf::Keyboard::Key a, sf::Keyboard::Key b, sf::Keyboard::Key c, sf::Keyboard::Key d) {
    return Math::Normalize(sf::Vector2f(Horizontal(a, b), Vertical(c, d)));
}

int fun::Input::LastKeyboardPressed() {
    return last_keyboard_key_pressed;
}
#endif



#if defined(ENABLE_JOYSTICKS)
bool fun::Input::IsJoystickConnected(int index) {
    return sf::Joystick::isConnected(index);
}

bool fun::Input::Pressed(JoystickButton button, int index) {
    return joystick_button_pressed[button][index];
}

bool fun::Input::Released(JoystickButton button, int index) {
    return joystick_button_released[button][index];
}

bool fun::Input::Hold(JoystickButton button, int index) {
    return joystick_button_hold[button][index];
}

float fun::Input::Value(JoystickAxis axis, int index) {
    auto jaxis = static_cast <sf::Joystick::Axis> (axis);

    if (IsJoystickConnected(index) && sf::Joystick::hasAxis(index, jaxis)) {
        float value = sf::Joystick::getAxisPosition(index, jaxis);

        if (axis == L2 || axis == R2) value = (value + 100) / 2;

        return value / 100;

    } else {
        return 0;
    }
}

sf::Vector2f fun::Input::J2D(Input::JoystickAxis a, Input::JoystickAxis b) {
    return Math::Normalize(sf::Vector2f(Value(a), Value(b)));
}
#endif