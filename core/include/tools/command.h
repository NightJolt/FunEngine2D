#pragma once

#include "../globals.h"

namespace fun {

    // cmd arg0 [ar g3] -flag0 -[fl ag1] key0:val0 [ke y1]:[va l1] ...

    class command_t {
    public:

        // command_t(int argc, char** argv);
        command_t() = default;
        explicit command_t(const std::string&);

        const std::string& get_command() const;
        const std::string& get_arg(uint32_t) const;
        const std::vector <std::string>& get_args() const;
        bool has_flag(const std::string&) const;
        bool has_key(const std::string&) const;
        const std::string& get_val(const std::string&) const;
        const std::vector <std::string>& get_vals(const std::string&) const;

        void set_command(const std::string&);
        void add_arg(const std::string&);

        std::string build() const; // ! NOT FINISHED

    private:

        std::unordered_map <std::string, std::vector <std::string>> m_key_vals;
        std::unordered_set <std::string> m_flags;
        std::vector <std::string> m_args;
        std::string m_command;
    };
}
