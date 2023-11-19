#include <generator.h>

int main(int argc, char** argv) {
    const char* rpc_file = argv[1];
    const char* output_file = argv[2];

    std::ifstream in(rpc_file);
    std::ofstream out(output_file);

    std::string buff;
    std::string rpc_code;

    while (in >> buff) {
        rpc_code += buff + " ";
    }

    std::cout << "rpc gen ===> in: " << rpc_file << " out: " << output_file << std::endl;

    out << fun::rpc::generate(rpc_code);

    in.close();
    out.close();

    return 0;
}
