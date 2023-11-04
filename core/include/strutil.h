#include "globals.h"

namespace fun::strutil {
    class tokens_iterator_t {
    public:
        tokens_iterator_t(std::vector<std::string_view>&);
        ~tokens_iterator_t();
        
        tokens_iterator_t(const tokens_iterator_t&) = delete;
        tokens_iterator_t& operator=(const tokens_iterator_t&) = delete;
        
        tokens_iterator_t(tokens_iterator_t&&);
        tokens_iterator_t& operator=(tokens_iterator_t&&);

        std::string_view current();
        void advance();
        bool is_empty();
        void reset();

        std::vector<std::string_view>& get_tokens();

    private:
        std::vector<std::string_view> tokens;
        uint32_t index = 0;
    };

    tokens_iterator_t tokenize(std::string&, std::vector<const char*>, bool = true);
    void filter_empty(tokens_iterator_t&);
}