#include "generator.h"

#include <FunEngine2D/core/include/strutil.h>

bool add_namespace(std::string& cpp, fun::strutil::tokens_iterator_t& tokens) {
    if (tokens.current() == "namespace") {
        tokens.advance();

        cpp += "namespace " + std::string(tokens.current()) + " {\n";
        
        return true;
    }

    return false;
}

void fun::rpc::generate() {
    std::string str = R"###(
        namespace space

        interface spawner {
            spawn : int32 x, int32 y
        }
    )###";
    fun::strutil::tokens_iterator_t tokens = fun::strutil::tokenize(str, { " ", "\n" });

    std::string cpp;
    
    bool has_namespace = add_namespace(cpp, tokens);

    if (has_namespace) {
        cpp += "}\n";
    }

    PRINTLN(cpp);
}
