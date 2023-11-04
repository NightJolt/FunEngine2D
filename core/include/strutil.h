#include "globals.h"

namespace fun::strutil {
    std::vector<std::string_view> tokenize(std::string&, std::vector<const char*>, bool = true);
    void filter_empty(std::vector<std::string_view>&);
}