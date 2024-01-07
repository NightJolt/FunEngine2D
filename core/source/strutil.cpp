#include "strutil.h"

namespace {
    struct delim_data_t {
        delim_data_t(const char* pat) : pat(pat) {
            len = strlen(pat);
            lps[0] = 0;
            ind = 0;

            uint32_t pat_ind = 0;

            for (uint32_t i = 1; i < len; i++) {
                if (pat[i] == pat[pat_ind]) {
                    lps[i] = ++pat_ind;
                } else {
                    if (pat_ind != 0) {
                        pat_ind = lps[pat_ind - 1];
                        i--;
                    } else {
                        lps[i] = 0;
                    }
                }
            }
        };

        const char* pat;
        uint32_t len;
        uint32_t lps[16];
        uint32_t ind;
    };

    bool is_empty_char(char c) {
        return c < 33;
    }
}

fun::strutil::tokens_iterator_t::tokens_iterator_t(std::vector<std::string_view>& tokens) : tokens(std::move(tokens)), index(0) {}
fun::strutil::tokens_iterator_t::~tokens_iterator_t() {
    tokens.clear();
    index = 0;
}

std::string_view fun::strutil::tokens_iterator_t::current() {
    return tokens[index];
}
        
fun::strutil::tokens_iterator_t::tokens_iterator_t(tokens_iterator_t&& other) {
    tokens = std::move(other.tokens);
    index = other.index;
}

fun::strutil::tokens_iterator_t& fun::strutil::tokens_iterator_t::operator=(tokens_iterator_t&& other) {
    if (this == &other) {
        return *this;
    }

    tokens = std::move(other.tokens);
    index = other.index;

    return *this;
}

void fun::strutil::tokens_iterator_t::advance() {
    index++;
}

bool fun::strutil::tokens_iterator_t::is_empty() {
    return index >= tokens.size();
}

void fun::strutil::tokens_iterator_t::reset() {
    index = 0;
}

std::string_view* fun::strutil::tokens_iterator_t::begin() {
    return &tokens[0];
}

std::string_view* fun::strutil::tokens_iterator_t::end() {
    return &tokens[0] + tokens.size();
}

std::vector<std::string_view>& fun::strutil::tokens_iterator_t::get_tokens() {
    return tokens;
}

fun::strutil::tokens_iterator_t fun::strutil::tokenize(const std::string& str, std::vector<const char*> delims, bool include_delims) {
    std::vector<std::string_view> tokens;
    std::vector<delim_data_t> delims_data;
    std::string_view str_view = str;

    for (const char* delim : delims) {
        delims_data.push_back(delim_data_t(delim));
    }

    int32_t count = 0;

    while (true) {
        for (auto& delim_data : delims_data) {
            delim_data_t* data = &delim_data;

            while (data->ind > 0 && str_view[count] != data->pat[data->ind]) {
                data->ind = data->lps[data->ind - 1];
            }

            if (str_view[count] == data->pat[data->ind]) {
                data->ind++;

                if (data->ind == data->len) {
                    uint32_t index = count - data->len + 1;

                    if (index > 0 && (index != 1 || !is_empty_char(str_view[0]))) {
                        tokens.push_back(str_view.substr(0, index));
                    }

                    if (include_delims && (data->len != 1 || !is_empty_char(data->pat[0]))) {
                        tokens.push_back(str_view.substr(index, data->len));
                    }

                    str_view = str_view.substr(count + 1);
                    count = -1;

                    break;
                }
            }
        }

        count++;

        if (count >= str_view.size()) {
            if (!str_view.empty()) {
                tokens.push_back(str_view);
            }

            break;
        }
    }

    tokens_iterator_t tokens_iterator(tokens);

    filter_empty(tokens_iterator);

    return std::move(tokens_iterator);
}

void fun::strutil::filter_empty(tokens_iterator_t& tokens_iterator_t) {
    uint32_t index = 0;
    auto& strs = tokens_iterator_t.get_tokens();

    for (auto it = strs.begin(); it != strs.end();) {
        std::string_view str = *it;
        bool empty = true;

        for (auto c : str) {
            empty &= is_empty_char(c);
        }
        
        if (empty) {
            it = strs.erase(it);
        } else {
            it++;
        }

        index++;
    }

    tokens_iterator_t.reset();
}
