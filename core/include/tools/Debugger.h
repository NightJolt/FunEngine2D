#pragma once

#include "../globals.h"

#include "Command.h"

namespace fun::debugger {
    void push_msg(const std::string&, const std::string& = "main");
    void push_cmd(const Command&, const std::string& = "main");

    void display();
}