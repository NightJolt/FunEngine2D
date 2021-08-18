#include "Tools/Command.h"

fun::Command::Command(const std::string& cmd) {
    key_vals = std::unordered_map <std::string, std::vector <std::string>> ();
    flags = std::unordered_set <std::string> ();
    args = std::vector <std::string> ();

    bool is_command = true;
    bool is_key = false;
    bool is_val = false;
    bool is_flag = false;
    bool is_arg = false;

    std::string key;
    std::string val;

    bool ignore_special_keys = false;
    bool ignore_brackets = false;

    for (int i = 0; i <= cmd.size(); i++) {
        char c = i == cmd.size() ? ' ' : cmd[i];

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
                command += c;
            }
        } else {
            if (c == ' ' && !ignore_special_keys) {
                if (is_arg) {
                    is_arg = false;

                    args.emplace_back(val);
                } else if (is_flag) {
                    is_flag = false;

                    flags.emplace(val);
                } else if (is_val) {
                    is_val = false;

                    if (val.length()) key_vals[key].emplace_back(val);
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

                    if (val.length()) key_vals[key].emplace_back(val);

                    val.clear();
                } else {
                    if (is_key) key += c;
                    else val += c;
                }
            }
        }
    }
}

const std::string& fun::Command::GetCommand() {
    return command;
}

const std::string& fun::Command::GetArgument(int index) {
    return args[index];
}

const std::vector <std::string>& fun::Command::GetArguments() {
    return args;
}

bool fun::Command::HasFlag(const std::string& flag) {
    return flags.contains(flag);
}

bool fun::Command::HasKey(const std::string& key) {
    return key_vals.contains(key);
}

const std::string& fun::Command::GetValueForKey(const std::string& key) {
    return key_vals[key][0];
}

const std::vector <std::string>& fun::Command::GetValuesForKey(const std::string& key) {
    return key_vals[key];
}