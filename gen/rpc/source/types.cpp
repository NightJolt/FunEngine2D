#include "types.h"

#include <FunEngine2D/core/include/strutil.h>
#include <FunEngine2D/core/include/iterator.h>

namespace {
    std::unordered_map <std::string, fun::cpp_type_element_t> cpp_type_elements = {
        { "void", { "void", true } },
        { "i8", { "int8_t", true } },
        { "i16", { "int16_t", true } },
        { "i32", { "int32_t", true } },
        { "i64", { "int64_t", true } },
        { "u8", { "uint8_t", true } },
        { "u16", { "uint16_t", true } },
        { "u32", { "uint32_t", true } },
        { "u64", { "uint64_t", true } },
        { "rgb", { "fun::rgb_t", true } },
        { "rgba", { "fun::rgba_t", true } },
        { "str", { "std::string", false } },
        { "bytes", { "fun::bytes_t", false } },
        { "vec", { "std::vector", false } },
    };
}

fun::rpc_type_t str_to_rpc_type(const std::string& str_type) {
    fun::rpc_type_t rpc_type;

    fun::strutil::tokens_iterator_t tokens = fun::strutil::tokenize(str_type, { "<", ">" }, false);
    fun::iterator_t<std::string_view> it(tokens.begin(), tokens.end());

    for (auto token : tokens) {
        std::string str_token(token);

        rpc_type.elements[rpc_type.elements_count++] = { str_token, cpp_type_elements.find(str_token) == cpp_type_elements.end() };
    }

    return rpc_type;
}

std::vector<fun::cpp_type_element_t> rpc_to_cpp_type_elements(const fun::rpc_type_element_t& rpc_type_element) {
    if (rpc_type_element.generated) {
        return {
            { "std::unique_ptr", false },
            // { "fun::rpc::stub_t", false },
            { "i_" + rpc_type_element.type + "_t", false },
        };
    }

    return { cpp_type_elements[rpc_type_element.type] };
}

std::string cpp_type_as_type(const fun::cpp_type_t& cpp_type) {
    std::string as_type = cpp_type.elements[0].type;
    bool is_trivially_copyable = cpp_type.elements[0].is_trivially_copyable;

    for (uint32_t i = 1; i < cpp_type.elements_count; i++) {
        as_type += "<" + cpp_type.elements[i].type;
    }

    for (uint32_t i = 1; i < cpp_type.elements_count; i++) {
        as_type += ">";
    }

    return as_type;
}

std::string cpp_type_as_ref(const fun::cpp_type_t& cpp_type) {
    return cpp_type.elements[0].is_trivially_copyable ? cpp_type.as_type : "const " + cpp_type.as_type + "&";
}

std::string cpp_type_as_template_args(const fun::cpp_type_t& cpp_type) {
    std::string as_template_args = cpp_type.elements[cpp_type.elements_count - 1].type;

    for (int32_t i = 0; i < cpp_type.elements_count - 1; i++) {
        as_template_args += ", " + cpp_type.elements[i].type;
    }

    return as_template_args;
}

fun::cpp_type_t rpc_to_cpp_type(const fun::rpc_type_t& rpc_type) {
    fun::cpp_type_t cpp_type;

    for (uint32_t i = 0; i < rpc_type.elements_count; i++) {
        auto elements = rpc_to_cpp_type_elements(rpc_type.elements[i]);

        for (auto element : elements) {
            cpp_type.elements[cpp_type.elements_count++] = element;
        }
    }

    cpp_type.as_type = cpp_type_as_type(cpp_type);
    cpp_type.as_ref = cpp_type_as_ref(cpp_type);
    cpp_type.as_template_args = cpp_type_as_template_args(cpp_type);

    return cpp_type;
}

fun::cpp_type_t fun::str_to_cpp_type(const std::string& str_type) {
    return rpc_to_cpp_type(str_to_rpc_type(str_type));
}

fun::cpp_type_t fun::str_to_cpp_type(std::string_view str_type) {
    return str_to_cpp_type(std::string(str_type));
}
