#include "generator.h"

#include <FunEngine2D/core/include/strutil.h>

void add_pragma_once(std::string& cpp) {
    cpp += "#pragma once\n\n";
}

void add_include_essentials(std::string& cpp) {
    cpp += "#include <FunEngine2D/core/include/globals.h>\n";
    cpp += "#include <FunEngine2D/core/include/rpc/rpc.h>\n";
    cpp += "#include <FunEngine2D/core/include/rpc/stub.h>\n";
    cpp += "\n";
}

std::string rpc_to_cpp_type(const std::string& type) {
    std::unordered_map <std::string, std::string> cpp_types = {
        { "void", "void"},
        { "i8", "int8_t" },
        { "i16", "int16_t" },
        { "i32", "int32_t" },
        { "i64", "int64_t" },
        { "u8", "uint8_t" },
        { "u16", "uint16_t" },
        { "u32", "uint32_t" },
        { "u64", "uint64_t" },
        // { "f32", "float" },
        // { "f64", "double" },
        { "str", "std::string" },
        { "bytes", "std::vector<uint8_t>" },
    };

    return cpp_types[type];
}

struct method_t {
    std::string return_type;
    std::string name;
    std::vector<std::pair<std::string, std::string>> args;
};

struct interface_t {
    std::string name;
    std::string base_name;
    std::vector<method_t> methods;
};

bool is_interface(fun::strutil::tokens_iterator_t& tokens) {
    return !tokens.is_empty() && tokens.current() == "interface";
}

method_t get_method(std::string& cpp, fun::strutil::tokens_iterator_t& tokens) {
    method_t method;

    method.return_type = rpc_to_cpp_type(std::string(tokens.current()));
    tokens.advance();

    method.name = std::string(tokens.current());
    tokens.advance();

    tokens.advance();

    while (true) {
        if (tokens.current() == ",") {
            tokens.advance();
        } else if (tokens.current() == ")") {
            break;
        }

        std::string type = rpc_to_cpp_type(std::string(tokens.current()));
        tokens.advance();
        
        std::string name = std::string(tokens.current());
        tokens.advance();

        method.args.push_back({ type, name });
    }

    tokens.advance();

    return method;
}

interface_t get_interface(std::string& cpp, fun::strutil::tokens_iterator_t& tokens) {
    interface_t interface;
    
    tokens.advance();

    interface.name = std::string(tokens.current());
    tokens.advance();

    interface.base_name = "i_" + std::string(interface.name) + "_t";

    tokens.advance();

    while (tokens.current() != "}") {
        interface.methods.push_back(get_method(cpp, tokens));
    }

    tokens.advance();

    return interface;
}

void def_interface_iid(std::string& cpp, const std::string& name) {
    cpp += "    static const fun::rpc::iid_t iid = " + std::to_string(std::hash<std::string>{}(name)) + ";\n\n";
}

void impl_method_base(std::string& cpp, method_t& method) {
    cpp += "    virtual " + method.return_type + " " + method.name + "(";

    for (uint32_t i = 0; i < method.args.size(); i++) {
        cpp += method.args[i].first + " " + method.args[i].second;

        if (i != method.args.size() - 1) {
            cpp += ", ";
        }
    }

    cpp += ") = 0;\n";
}

void impl_interface_base(std::string& cpp, interface_t& interface) {
    cpp += "struct " + interface.base_name + " : public fun::rpc::i_hollow_t {\n";

    def_interface_iid(cpp, interface.name);

    for (method_t& method : interface.methods) {
        impl_method_base(cpp, method);
    }

    cpp += "};\n";
}

void impl_method_stub_ret(std::string& cpp, method_t& method) {
    cpp += "        " + method.return_type + " ret;\n";
    cpp += "        auto sync_call_data_extractor = [&ret](fun::rpc::deserializer_t& deserializer) {\n";
    cpp += "            ret = deserializer.deserialize<" + method.return_type + ">();\n";
    cpp += "        };\n\n";
    cpp += "        wait_for_sync_call_reply(connection_provider, sync_call_data_extractor);\n\n";
    cpp += "        return ret;\n";
}

void impl_method_stub(std::string& cpp, method_t& method, uint32_t method_id) {
    cpp += "    " + method.return_type + " " + method.name + "(";

    for (uint32_t i = 0; i < method.args.size(); i++) {
        cpp += method.args[i].first + " " + method.args[i].second;

        if (i != method.args.size() - 1) {
            cpp += ", ";
        }
    }

    cpp += ") override {\n";
    cpp += "        fun::rpc::serializer_t serializer;\n\n";

    cpp += "        serializer.serialize<fun::rpc::oid_t>(owner_oid);\n";
    cpp += "        serializer.serialize<fun::rpc::iid_t>(iid);\n";
    cpp += "        serializer.serialize<fun::rpc::mid_t>(" + std::to_string(method_id) + ");\n";

    for (uint32_t i = 0; i < method.args.size(); i++) {
        cpp += "        serializer.serialize<" + method.args[i].first + ">(" + method.args[i].second + ");\n";
    }

    cpp += "\n        connection_provider.get_connection(owner_addr).send(serializer.get_data(), serializer.get_size());\n";

    if (method.return_type != "void") {
        cpp += "\n";
        impl_method_stub_ret(cpp, method);
    }

    cpp += "    }\n";
}

void impl_interface_stub(std::string& cpp, interface_t& interface) {
    cpp += "struct " + interface.name + "_stub_t : public fun::rpc::stub_t<" + interface.base_name + "> {\n";
    cpp += "    " + interface.name + "_stub_t(fun::rpc::addr_t owner_addr, fun::rpc::oid_t owner_oid, fun::rpc::connection_provider_t& connection_provider) :\n";
    cpp += "        fun::rpc::stub_t<" + interface.base_name + ">(owner_addr, owner_oid, connection_provider) {}\n";

    uint32_t method_id = 0;
    for (method_t& method : interface.methods) {
        cpp += "\n";
        impl_method_stub(cpp, method, method_id++);
    }

    cpp += "};\n";
}

void impl_interface_stub_factory(std::string& cpp, interface_t& interface) {
    cpp += "inline fun::rpc::i_hollow_t* rpc__" + interface.name + "__stub_factory(fun::rpc::addr_t owner_addr, fun::rpc::oid_t owner_oid, fun::rpc::connection_provider_t& connection_provider) {\n";
    cpp += "    return new " + interface.name + "_stub_t(owner_addr, owner_oid, connection_provider);\n";
    cpp += "}\n";
}

void impl_interface_invokable_no_ret(std::string& cpp, interface_t& interface, method_t& method) {
    cpp += "inline void rpc__" + interface.name + "__" + method.name + "(fun::rpc::deserializer_t& deserializer, " + interface.base_name + "* " + interface.name + "_object) {\n";
    cpp += "    " + interface.name + "_object->" + method.name + "(";

    for (uint32_t i = 0; i < method.args.size(); i++) {
        cpp += "deserializer.deserialize<" + method.args[i].first + ">()";

        if (i != method.args.size() - 1) {
            cpp += ", ";
        }
    }

    cpp += ");\n";
    cpp += "}\n\n";
}

void impl_interface_invokable_ret(std::string& cpp, interface_t& interface, method_t& method) {
    cpp += "inline void rpc__" + interface.name + "__" + method.name + "(fun::rpc::deserializer_t& deserializer, " + interface.base_name + "* " + interface.name + "_object, fun::rpc::serializer_t& serializer) {\n";
    cpp += "    " + method.return_type + " ret = " + interface.name + "_object->" + method.name + "(";

    for (uint32_t i = 0; i < method.args.size(); i++) {
        cpp += "deserializer.deserialize<" + method.args[i].first + ">()";

        if (i != method.args.size() - 1) {
            cpp += ", ";
        }
    }

    cpp += ");\n\n";
    
    cpp += "    serializer.serialize<fun::rpc::oid_t>(0);\n";
    cpp += "    serializer.serialize<fun::rpc::mid_t>(1);\n";
    cpp += "    serializer.serialize<" + method.return_type + ">(ret);\n";
    cpp += "}\n\n";
}

void impl_interface_invokables(std::string& cpp, interface_t& interface) {
    for (method_t& method : interface.methods) {
        if (method.return_type == "void") {
            impl_interface_invokable_no_ret(cpp, interface, method);
        } else {
            impl_interface_invokable_ret(cpp, interface, method);
        }
    }
}

void impl_method_invoker(std::string& cpp, interface_t& interface, method_t& method, uint32_t method_id) {
    cpp += "        case " + std::to_string(method_id) + ": {\n";

    if (method.return_type == "void") {
        cpp += "            rpc__" + interface.name + "__" + method.name + "(deserializer, " + interface.name + "_object);\n";
    } else {
        cpp += "            rpc__" + interface.name + "__" + method.name + "(deserializer, " + interface.name + "_object, serializer);\n";
    }

    cpp += "            break;\n";
    cpp += "        }\n";
}

void impl_interface_invoker(std::string& cpp, interface_t& interface) {
    cpp += "inline void rpc__" + interface.name + "_invoker(fun::rpc::deserializer_t& deserializer, fun::rpc::i_hollow_t* object, fun::rpc::serializer_t& serializer) {\n";
    cpp += "    fun::rpc::mid_t method_id = deserializer.deserialize<fun::rpc::mid_t>();\n";
    cpp += "    " + interface.base_name + "* " + interface.name + "_object = static_cast<" + interface.base_name + "*>(object);\n\n";
    
    cpp += "    switch(method_id) {\n";

    uint32_t method_id = 0;
    for (method_t& method : interface.methods) {
        impl_method_invoker(cpp, interface, method, method_id++);
    }

    cpp += "    }\n";
    cpp += "}\n";
}

void impl_interface_registrator(std::string& reg, interface_t& interface) {
    reg += "    rpc.get_invoker().register_interface(" + interface.base_name + "::iid, rpc__" + interface.name + "_invoker);\n";
    reg += "    rpc.get_stub_factory().register_interface(" + interface.base_name + "::iid, rpc__" + interface.name + "__stub_factory);\n";
}

void impl_interface(std::string& cpp, interface_t& interface) {
    impl_interface_base(cpp, interface); cpp += "\n";
    impl_interface_stub(cpp, interface); cpp += "\n";
    impl_interface_stub_factory(cpp, interface); cpp += "\n";
    impl_interface_invokables(cpp, interface);
    impl_interface_invoker(cpp, interface); cpp += "\n";
}

bool begin_namespace(std::string& cpp, fun::strutil::tokens_iterator_t& tokens) {
    if (tokens.current() != "namespace") {
        return false;
    }

    tokens.advance();

    cpp += "namespace " + std::string(tokens.current()) + " {\n\n";
    tokens.advance();
    
    return true;
}

void end_namespace(std::string& cpp) {
    cpp += "}\n";
}

std::string fun::rpc::generate(std::string& rpc_file) {
    fun::strutil::tokens_iterator_t tokens = fun::strutil::tokenize(rpc_file, { " ", "\n", "{", "}", "(", ")", "," });

    std::string cpp;
    std::string reg;

    add_pragma_once(cpp);
    add_include_essentials(cpp);
    
    bool has_namespace = begin_namespace(cpp, tokens);
    
    reg += "inline void register_rpc_interfaces(fun::rpc::rpc_t& rpc) {\n";

    while (is_interface(tokens)) {
        interface_t interface = get_interface(cpp, tokens);

        impl_interface(cpp, interface);
        impl_interface_registrator(reg, interface);
    }

    reg += "}\n\n";
    cpp += reg;

    if (has_namespace) {
        end_namespace(cpp);
    }

    return cpp;
}
