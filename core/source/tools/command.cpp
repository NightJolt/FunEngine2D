#include "tools/command.h"

fun::command_t::command_t(const std::string& cmd) :

m_key_vals(std::unordered_map <std::string, std::vector <std::string>> ()),
m_flags(std::unordered_set <std::string> ()),
m_args(std::vector <std::string> ())

{
    bool is_command = true;
    bool is_key = false;
    bool is_val = false;
    bool is_flag = false;
    bool is_arg = false;

    std::string key;
    std::string val;

    bool ignore_special_keys = false;
    bool ignore_brackets = false;

    for (uint32_t i = 0; i <= cmd.size(); i++) {
        char c = i == cmd.size() ? ' ' : cmd[i];

        if (i == 0 && c == '/') continue;

        if ((c == '[' || c == ']') && !ignore_brackets) {
            ignore_special_keys = c == '[';

            continue;
        }

        if (c == '$' && !ignore_brackets) {
            ignore_brackets = true;

            continue;
        }

        ignore_brackets = false;

        if (is_command) {
            if (c == ' ' && !ignore_special_keys) {
                is_command = false;
            } else {
                m_command.push_back(c);
            }
        } else {
            if (c == ' ' && !ignore_special_keys) {
                if (is_arg) {
                    is_arg = false;

                    m_args.emplace_back(val);
                } else if (is_flag) {
                    is_flag = false;

                    m_flags.emplace(val);
                } else if (is_val) {
                    is_val = false;

                    if (val.length()) m_key_vals[key].emplace_back(val);
                } else if (is_key) is_key = false;

                key.clear();
                val.clear();
            } else if (!is_key && !is_flag && !is_val && val.empty()) {
                if (c == '+' && !ignore_special_keys) {
                    is_key = true;
                } else if (c == '-' && !ignore_special_keys) {
                    is_flag = true;
                } else {
                    is_arg = true;

                    val += c;
                }
            } else {
                if (key.length() && !ignore_special_keys && (c == ':' || c == ',')) {
                    is_key = false;
                    is_val = true;

                    if (val.length()) m_key_vals[key].emplace_back(val);

                    val.clear();
                } else {
                    if (is_key) key += c;
                    else val += c;
                }
            }
        }
    }
}

const std::string& fun::command_t::get_command() {
    return m_command;
}

const std::string& fun::command_t::get_arg(uint32_t index) {
    return m_args[index];
}

const std::vector <std::string>& fun::command_t::get_args() {
    return m_args;
}

bool fun::command_t::has_flag(const std::string& flag) {
    return m_flags.contains(flag);
}

bool fun::command_t::has_key(const std::string& key) {
    return m_key_vals.contains(key);
}

const std::string& fun::command_t::get_val(const std::string& key) {
    return m_key_vals[key][0];
}

const std::vector <std::string>& fun::command_t::get_vals(const std::string& key) {
    return m_key_vals[key];
}