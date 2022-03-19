#pragma once

#include "../globals.h"
#include "command.h"
#include "../resources.h"
#include "../render/window_manager.h"

namespace fun::debugger {
    void display_debug_menu();

    void display_unit_coord(const vec2f_t&, float, layer_t, sf::Color, const std::string&);

    void push_msg(const std::string&, const std::string& = "main");
    void push_cmd(const command_t&, const std::string& = "main");
    void display_debug_log();

    void log(std::string);

    // void display_unit_lines(uint32_t, sf::Color, const std::string&);
}