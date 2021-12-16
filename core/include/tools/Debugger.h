#pragma once

#include "../globals.h"

#include "Command.h"

namespace fun::debugger {
    void push_msg(const std::string&, const std::string& = "main");
    void push_cmd(const Command&, const std::string& = "main");

    void display();

    extern std::string buffer;
    extern std::unordered_map <std::string, std::string> channels;
    extern std::unordered_map <std::string, std::vector <std::string>> logs;
    extern std::vector <std::pair <std::string*, std::string*>> order;
}