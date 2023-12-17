#include "generator.h"

int main(int argc, char** argv) {
    const char* rpc_file = argv[1];
    const char* output_file = argv[2];

    std::cout << "rpc gen ===> in: " << rpc_file << " out: " << output_file << std::endl;

    std::filesystem::create_directories(std::filesystem::path(output_file).parent_path());

    std::ifstream in(rpc_file);
    if (!in.is_open()) {
        std::cout << "could not open in file: " << rpc_file << std::endl;
    }

    std::ofstream out(output_file);
    if (!out.is_open()) {
        std::cout << "could not open out file: " << output_file << std::endl;
    }

    std::string buff;
    std::string rpc_code;

    while (in >> buff) {
        rpc_code += buff + " ";
    }

    out << fun::rpc::generate(rpc_code);

    in.close();
    out.close();

    return 0;
}
