#include "input.h"
#include "_math.h"

#if defined(ENABLE_MOUSE)
static bool _mouse_button_pressed_[MOUSE_BUTTON_COUNT];
static bool _mouse_button_released_[MOUSE_BUTTON_COUNT];
static bool _mouse_button_hold_[MOUSE_BUTTON_COUNT];

static fun::vec2f_t _mouse_position_ = fun::vec2f_t();
static fun::vec2f_t _mouse_delta_ = fun::vec2f_t();
#endif

#if defined(ENABLE_KEYBOARD)
static bool _keyboard_key_pressed_[KEYBOARD_KEY_COUNT];
static bool _keyboard_key_released_[KEYBOARD_KEY_COUNT];
static bool _keyboard_key_hold_[KEYBOARD_KEY_COUNT];
#endif

#if defined(ENABLE_GAMEPAD)
static bool _gamepad_button_pressed_[GAMEPAD_BUTTON_COUNT][MAX_GAMEPAD_COUNT];
static bool _gamepad_button_released_[GAMEPAD_BUTTON_COUNT][MAX_GAMEPAD_COUNT];
static bool _gamepad_button_hold_[GAMEPAD_BUTTON_COUNT][MAX_GAMEPAD_COUNT];
#endif

void fun::input::listen(bool is_focused) {
#if defined(ENABLE_MOUSE)
    for (int button = 0; button < MOUSE_BUTTON_COUNT; button++) {
        _mouse_button_pressed_[button] = false;
        _mouse_button_released_[button] = false;

        bool is_button_pressed = sf::Mouse::isButtonPressed(static_cast <sf::Mouse::Button> (button));
        bool is_imgui_blocking = false;

#if defined(USES_IMGUI)
        is_imgui_blocking = ImGui::GetIO().WantCaptureMouse;
#endif

        if (is_focused && is_button_pressed && !is_imgui_blocking) {
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

    _mouse_delta_ = (vec2f_t)(vec2i_t)sf::Mouse::getPosition() - _mouse_position_;
    _mouse_position_ += _mouse_delta_;
#endif

#if defined(ENABLE_KEYBOARD)
    for (int key = 0; key < KEYBOARD_KEY_COUNT; key++) {
        _keyboard_key_pressed_[key] = false;
        _keyboard_key_released_[key] = false;

        if (is_focused && sf::Keyboard::isKeyPressed(static_cast <sf::Keyboard::Key> (key))) {
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

#if defined(ENABLE_GAMEPAD)
    for (int button = 0; button < GAMEPAD_BUTTON_COUNT; button++) {
        for (int index = 0; index < MAX_GAMEPAD_COUNT; index++) {
            _gamepad_button_pressed_[button][index] = false;
            _gamepad_button_released_[button][index] = false;

            if (is_gamepad_connected(index)) {
                if (is_focused && sf::Joystick::isButtonPressed(index, button)) {
                    if (_gamepad_button_hold_[button][index]) {
                        _gamepad_button_pressed_[button][index] = true;
                        _gamepad_button_hold_[button][index] = true;
                    }
                } else {
                    if (_gamepad_button_hold_[button][index]) {
                        _gamepad_button_hold_[button][index] = false;
                        _gamepad_button_released_[button][index] = true;
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

fun::vec2f_t fun::input::mouse_2d() {
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

fun::vec2f_t fun::input::keyboard_2d(sf::Keyboard::Key a, sf::Keyboard::Key b, sf::Keyboard::Key c, sf::Keyboard::Key d) {
    return math::normalize(vec2f_t(horizontal(a, b), vertical(c, d)));
}
#endif



#if defined(ENABLE_GAMEPAD)
bool fun::input::is_gamepad_connected(int index) {
    return sf::Joystick::isConnected(index);
}

bool fun::input::pressed(gamepad_button_t button, int index) {
    return _gamepad_button_pressed_[button][index];
}

bool fun::input::released(gamepad_button_t button, int index) {
    return _gamepad_button_released_[button][index];
}

bool fun::input::hold(gamepad_button_t button, int index) {
    return _gamepad_button_hold_[button][index];
}

float fun::input::value(gamepad_axis_t axis, int index) {
    auto jaxis = static_cast <sf::Joystick::Axis> (axis);

    if (is_gamepad_connected(index) && sf::Joystick::hasAxis(index, jaxis)) {
        float value = sf::Joystick::getAxisPosition(index, jaxis);

        // if (axis == L2 || axis == R2) value = (value + 100) / 2;

        return value / 100;

    } else {
        return 0;
    }
}

fun::vec2f_t fun::input::gamepad_2d(gamepad_axis_t a, gamepad_axis_t b) {
    return math::normalize(vec2f_t(value(a), value(b)));
}
#endif
