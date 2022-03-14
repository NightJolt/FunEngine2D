#pragma once

#include "../Globals.h"

namespace fun {
    class Command {
    public:

        explicit Command(const std::string&);

        const std::string& GetCommand();
        const std::string& GetArgument(uint32_t);
        const std::vector <std::string>& GetArguments();
        bool HasFlag(const std::string&);
        bool HasKey(const std::string&);
        const std::string& GetValueForKey(const std::string&);
        const std::vector <std::string>& GetValuesForKey(const std::string&);

    private:

        std::unordered_map <std::string, std::vector <std::string>> key_vals;
        std::unordered_set <std::string> flags;
        std::vector <std::string> args;
        std::string command;
    };
}