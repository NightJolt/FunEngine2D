#pragma once

#include "globals.h"
#include "_math.h"
#include "vec2.h"
#include "render/window_manager.h"

#define ENABLE_MOUSE
#define ENABLE_KEYBOARD
#define ENABLE_GAMEPAD

#define KEYBOARD_KEY_COUNT sf::Keyboard::Key::KeyCount
#define MOUSE_BUTTON_COUNT sf::Mouse::Button::ButtonCount
#define GAMEPAD_BUTTON_COUNT fun::input::gamepad_button_count
#define GAMEPAD_AXIS_COUNT fun::input::gamepad_axis_count
#define MAX_GAMEPAD_COUNT 8

namespace fun::input {
    void listen();

#if defined(ENABLE_MOUSE)
    bool pressed(sf::Mouse::Button);
    bool released(sf::Mouse::Button);
    bool hold(sf::Mouse::Button);
    fun::vec2f_t mouse_2d();
#endif

#if defined(ENABLE_KEYBOARD)
    bool pressed(sf::Keyboard::Key);
    bool released(sf::Keyboard::Key);
    bool hold(sf::Keyboard::Key);
    int horizontal(sf::Keyboard::Key = sf::Keyboard::Key::A, sf::Keyboard::Key = sf::Keyboard::Key::D);
    int vertical(sf::Keyboard::Key = sf::Keyboard::Key::S, sf::Keyboard::Key = sf::Keyboard::Key::W);
    fun::vec2f_t keyboard_2d(
            sf::Keyboard::Key = sf::Keyboard::Key::A,
            sf::Keyboard::Key = sf::Keyboard::Key::D,
            sf::Keyboard::Key = sf::Keyboard::Key::S,
            sf::Keyboard::Key = sf::Keyboard::Key::W
    );
#endif

#if defined(ENABLE_GAMEPAD)
    enum gamepad_button_t {
        x,
        o,
        t,
        r,
        l1,
        r1,
        l2i,
        r2i,

        gamepad_button_count
    };

    enum gamepad_axis_t {
        l3x,
        l3y,
        l2,
        r2,
        r3x,
        r3y,
        dx,
        dy,

        gamepad_axis_count
    };

    bool is_gamepad_connected(int = 0);
    bool pressed(gamepad_button_t, int = 0);
    bool released(gamepad_button_t, int = 0);
    bool hold(gamepad_button_t, int = 0);
    float value(gamepad_axis_t, int = 0);
    fun::vec2f_t gamepad_2d(
            gamepad_axis_t = gamepad_axis_t::l3x,
            gamepad_axis_t = gamepad_axis_t::l3y
    );
#endif
}
