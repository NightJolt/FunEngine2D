#pragma once

#include "../globals.h"
#include "../vec2.h"

namespace fun::debugger {
    void display();

    void display_debug_log();
    void display_unit_coord(const vec2f_t&, float, layer_t, sf::Color, const std::string&);
    void display_interaction_debug_menu();

    void push_msg(const std::string&, const std::string& = "main");
    void push_cmd(const command_t&, const std::string& = "main");

    void print_synced(std::string);
}
