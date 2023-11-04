#include "strutil.h"

namespace {
    struct delim_data_t {
        delim_data_t(const char* pat) : pat(pat) {
            uint32_t len = strlen(pat);
            uint32_t ind = 0;

            lps[0] = 0;

            for (uint32_t i = 1; i < len; i++) {
                if (pat[i] == pat[ind]) {
                    lps[i] = ++ind;
                } else {
                    if (ind != 0) {
                        ind = lps[ind - 1];
                        i--;
                    } else {
                        lps[i] = 0;
                    }
                }
            }
        };

        const char* pat;
        uint32_t lps[16];
        uint32_t ind = 0;
    };
}

std::vector<std::string_view> fun::strutil::tokenize(std::string& str, std::vector<const char*> delims, bool include_delims) {
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

                if (data->ind == strlen(data->pat)) {
                    uint32_t index = count - strlen(data->pat) + 1;

                    tokens.push_back(str_view.substr(0, index));

                    if (include_delims) {
                        tokens.push_back(str_view.substr(index, strlen(data->pat)));
                    }

                    str_view = str_view.substr(count + 1);
                    count = -1;

                    break;
                }
            }
        }

        count++;

        if (count >= str_view.size()) {
            tokens.push_back(str_view);

            break;
        }
    }

    filter_empty(tokens);

    return tokens;
}

void fun::strutil::filter_empty(std::vector<std::string_view>& strs) {
    uint32_t index = 0;

    for (auto it = strs.begin(); it != strs.end();) {
        std::string_view str = *it;
        bool empty = true;

        for (auto c : str) {
            empty &= c < 33;
        }
        
        if (empty) {
            it = strs.erase(it);
        } else {
            it++;
        }

        index++;
    }
}
