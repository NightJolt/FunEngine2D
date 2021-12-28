#include "Input.h"

#if defined(ENABLE_MOUSE)
static bool _mouse_button_pressed_[MOUSE_BUTTON_COUNT];
static bool _mouse_button_released_[MOUSE_BUTTON_COUNT];
static bool _mouse_button_hold_[MOUSE_BUTTON_COUNT];

static sf::Vector2f _mouse_position_ = sf::Vector2f(0, 0);
static sf::Vector2f _mouse_delta_ = sf::Vector2f(0, 0);
#endif

#if defined(ENABLE_KEYBOARD)
static bool _keyboard_key_pressed_[KEYBOARD_KEY_COUNT];
static bool _keyboard_key_released_[KEYBOARD_KEY_COUNT];
static bool _keyboard_key_hold_[KEYBOARD_KEY_COUNT];
#endif

#if defined(ENABLE_JOYSTICKS)
static bool _joystick_button_pressed_[JOYSTICK_BUTTON_COUNT][MAX_JOYSTICK_COUNT];
static bool _joystick_button_released_[JOYSTICK_BUTTON_COUNT][MAX_JOYSTICK_COUNT];
static bool _joystick_button_hold_[JOYSTICK_BUTTON_COUNT][MAX_JOYSTICK_COUNT];
#endif

void fun::input::listen() {
#if defined(ENABLE_MOUSE)
    for (int button = 0; button < MOUSE_BUTTON_COUNT; button++) {
        _mouse_button_pressed_[button] = false;
        _mouse_button_released_[button] = false;

        if (sf::Mouse::isButtonPressed(static_cast <sf::Mouse::Button> (button))) {
            if (!_mouse_button_hold_[button]) {
                _mouse_button_pressed_[button] = true;
                _mouse_button_hold_[button] = true;
            }
        } else {
            if (_mouse_button_hold_[button]) {
                _mouse_button_hold_[button] = false;
                _mouse_button_released_[button] = true;
            }
        }
    }

    _mouse_delta_ = (sf::Vector2f)sf::Mouse::getPosition() - _mouse_position_;
    _mouse_position_ += _mouse_delta_;
#endif

#if defined(ENABLE_KEYBOARD)
    for (int key = 0; key < KEYBOARD_KEY_COUNT; key++) {
        _keyboard_key_pressed_[key] = false;
        _keyboard_key_released_[key] = false;

        if (sf::Keyboard::isKeyPressed(static_cast <sf::Keyboard::Key> (key))) {
            if (!_keyboard_key_hold_[key]) {
                _keyboard_key_pressed_[key] = true;
                _keyboard_key_hold_[key] = true;
            }
        } else {
            if (_keyboard_key_hold_[key]) {
                _keyboard_key_hold_[key] = false;
                _keyboard_key_released_[key] = true;
            }
        }
    }
#endif

#if defined(ENABLE_JOYSTICKS)
    for (int button = 0; button < JOYSTICK_BUTTON_COUNT; button++) {
        for (int index = 0; index < MAX_JOYSTICK_COUNT; index++) {
            _joystick_button_pressed_[button][index] = false;
            _joystick_button_released_[button][index] = false;

            if (is_joystick_connected(index)) {
                if (sf::Joystick::isButtonPressed(index, button)) {
                    if (_joystick_button_hold_[button][index]) {
                        _joystick_button_pressed_[button][index] = true;
                        _joystick_button_hold_[button][index] = true;
                    }
                } else {
                    if (_joystick_button_hold_[button][index]) {
                        _joystick_button_hold_[button][index] = false;
                        _joystick_button_released_[button][index] = true;
                    }
                }
            }
        }
    }
#endif
}



#if defined(ENABLE_MOUSE)
bool fun::input::pressed(sf::Mouse::Button button) {
    return _mouse_button_pressed_[button];
}

bool fun::input::released(sf::Mouse::Button button) {
    return _mouse_button_released_[button];
}

bool fun::input::hold(sf::Mouse::Button button) {
    return _mouse_button_hold_[button];
}

sf::Vector2f fun::input::mouse_2d() {
    return _mouse_delta_;
}
#endif



#if defined(ENABLE_KEYBOARD)
bool fun::input::pressed(sf::Keyboard::Key key) {
    return _keyboard_key_pressed_[key];
}

bool fun::input::released(sf::Keyboard::Key key) {
    return _keyboard_key_released_[key];
}

bool fun::input::hold(sf::Keyboard::Key key) {
    return _keyboard_key_hold_[key];
}

int fun::input::horizontal(sf::Keyboard::Key a, sf::Keyboard::Key b) {
    return _keyboard_key_hold_[b] - _keyboard_key_hold_[a];
}

int fun::input::vertical(sf::Keyboard::Key a, sf::Keyboard::Key b) {
    return _keyboard_key_hold_[b] - _keyboard_key_hold_[a];
}

sf::Vector2f fun::input::keyboard_2d(sf::Keyboard::Key a, sf::Keyboard::Key b, sf::Keyboard::Key c, sf::Keyboard::Key d) {
    return math::normalize(sf::Vector2f(horizontal(a, b), vertical(c, d)));
}
#endif



#if defined(ENABLE_JOYSTICKS)
bool fun::input::is_joystick_connected(int index) {
    return sf::Joystick::isConnected(index);
}

bool fun::input::pressed(JoystickButton button, int index) {
    return _joystick_button_pressed_[button][index];
}

bool fun::input::released(JoystickButton button, int index) {
    return _joystick_button_released_[button][index];
}

bool fun::input::hold(JoystickButton button, int index) {
    return _joystick_button_hold_[button][index];
}

float fun::input::value(JoystickAxis axis, int index) {
    auto jaxis = static_cast <sf::Joystick::Axis> (axis);

    if (is_joystick_connected(index) && sf::Joystick::hasAxis(index, jaxis)) {
        float value = sf::Joystick::getAxisPosition(index, jaxis);

        if (axis == L2 || axis == R2) value = (value + 100) / 2;

        return value / 100;

    } else {
        return 0;
    }
}

sf::Vector2f fun::input::joystick_2d(JoystickAxis a, JoystickAxis b) {
    return math::normalize(sf::Vector2f(value(a), value(b)));
}
#endif