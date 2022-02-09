#pragma once

#include "../Globals.h"
#include "Command.h"
#include "../Resources.h"
#include "../render/WindowManager.h"

namespace fun::debugger {
    void display_debug_menu();

    void display_unit_coord(const sf::Vector2f&, float, int, sf::Color, const std::string&);

    void push_msg(const std::string&, const std::string& = "main");
    void push_cmd(const Command&, const std::string& = "main");
    void display_debug_log();

    // void display_unit_lines(uint32_t, sf::Color, const std::string&);
}