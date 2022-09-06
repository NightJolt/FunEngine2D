#include "tools/command.h"

fun::command_t::command_t(const std::string& cmd) {
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

const std::string& fun::command_t::get_command() const {
    return m_command;
}

const std::string& fun::command_t::get_arg(uint32_t index) const {
    return m_args[index];
}

const std::vector <std::string>& fun::command_t::get_args() const {
    return m_args;
}

bool fun::command_t::has_flag(const std::string& flag) const {
    return m_flags.contains(flag);
}

bool fun::command_t::has_key(const std::string& key) const {
    return m_key_vals.contains(key);
}

const std::string& fun::command_t::get_val(const std::string& key) const {
    return m_key_vals.at(key)[0];
}

const std::vector <std::string>& fun::command_t::get_vals(const std::string& key) const {
    return m_key_vals.at(key);
}

void fun::command_t::set_command(const std::string& cmd) {
    m_command = cmd;
}

std::string fun::command_t::format(const std::string& arg) const {
    std::string arg_cpy;
    arg_cpy.reserve(arg.size() * 1.2f);

    bool apply_guard = false;

    for (int i = 0; i < arg.size(); i++) {
        if (arg[i] == ' ' || arg[i] == '-' || arg[i] == '+') apply_guard = true;
        if (arg[i] == '[' || arg[i] == ']' || arg[i] == '$') arg_cpy += '$';

        arg_cpy += arg[i];
    }

    if (apply_guard) {
        arg_cpy =  '[' + arg_cpy + ']';
    }

    return arg_cpy;
}

void fun::command_t::add_arg(const std::string& arg) {
    m_args.emplace_back(arg);
}

void fun::command_t::add_flag(const std::string& flag) {
    m_flags.emplace(flag);
}

void fun::command_t::add_key_val(const std::string& key, const std::string& val) {
    m_key_vals[key].emplace_back(val);
}

std::string fun::command_t::build() const {
    std::string cmd(m_command);

    for (auto& arg : m_args) {
        cmd += " " + format(arg);
    }

    for (auto& flag : m_flags) {
        cmd += " -" + format(flag);
    }

    for (auto& [key, vals] : m_key_vals) {
        cmd += " +" + format(key) + ":";

        for (int i = 0; i < vals.size(); i++) {
            cmd += format(vals[i]);

            if (i != vals.size() - 1) cmd += ",";
        }
    }

    return cmd;
}