#pragma once

#include "../globals.h"

namespace fun {
    class command_t {
    public:

        explicit command_t(const std::string&);

        const std::string& get_command();
        const std::string& get_arg(uint32_t);
        const std::vector <std::string>& get_args();
        bool has_flag(const std::string&);
        bool has_key(const std::string&);
        const std::string& get_val(const std::string&);
        const std::vector <std::string>& get_vals(const std::string&);

    private:

        std::unordered_map <std::string, std::vector <std::string>> m_key_vals;
        std::unordered_set <std::string> m_flags;
        std::vector <std::string> m_args;
        std::string m_command;
    };
}
