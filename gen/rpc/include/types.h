#pragma once

#include <FunEngine2D/core/include/globals.h>

namespace fun {
    struct rpc_type_element_t {
        std::string type;
        bool generated = false;
    };

    struct rpc_type_t {
        rpc_type_element_t elements[4];
        uint32_t elements_count = 0;
    };

    struct cpp_type_element_t {
        std::string type;
        bool is_trivially_copyable = true;
    };

    struct cpp_type_t {
        cpp_type_element_t elements[8];
        uint32_t elements_count = 0;

        std::string as_type;
        std::string as_ref;
        std::string as_template_args;
    };

    fun::cpp_type_t str_to_cpp_type(const std::string&);
    fun::cpp_type_t str_to_cpp_type(std::string_view);
}