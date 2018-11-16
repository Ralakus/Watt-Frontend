#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <vector>

namespace Watt {
    constexpr const char version[] = "0.1.0";

    void print_version() {
        std::cout << "Watt frontend version " << Watt::version << std::endl; 
    }

    void print_help() {
        print_version();
        std::cout << "-h or --help to print help" << std::endl;
        std::cout << "-f or --file <file> to compile files" << std::endl;
        std::cout << "-v or --version for version info" << std::endl;
    }

    bool read_file(std::string& str, const std::string_view& file_name) {

        std::ifstream file(file_name.data(), std::ios::binary | std::ios::ate);

        if(!file.is_open()) {
            std::cout << "Failed to read file \"" << file_name << "\"!" << std::endl;
            return false;
        }

        size_t size = file.tellg();
        str.resize(size, '\0');
        file.seekg(0);
        file.read(&str[0], size);

        file.close();

        return true;        
    } 

}


int main(int argc, char* argv[]) {

    std::vector<std::string_view> args{argv + 1, argv + argc};

    if(args.size() == 0) {
        std::cout << "No arguments!" << std::endl;
        return EXIT_FAILURE;
    }

    std::vector<std::pair<std::string_view, std::string>> files;  // Filename, file contents

    enum class arg_parse_state {
        other, files
    } parse_state;

    for(const auto& arg : args) {

        if(arg=="-h" || arg=="--help") {
            Watt::print_help();
            return EXIT_SUCCESS;
        } 

        else if (arg=="-f" || arg=="--file") {
            parse_state = arg_parse_state::files;
            continue;
        }

        else if(arg=="-v" || arg=="--version") {
            Watt::print_version();
            return EXIT_SUCCESS;
        }

        else if(arg=="--repl") {
            std::cout << "REPL compilation is not supported yet" << std::endl;
            return EXIT_SUCCESS;
        }

        else if(parse_state == arg_parse_state::files) {
            files.emplace_back(std::make_pair(arg, std::string()));
            if(!Watt::read_file(files.back().second, files.back().first)) {
                return EXIT_FAILURE;
            }
        }

        else {
            std::cout << "Invalid argument: \"" << arg << '\"' << std::endl;
            Watt::print_help();
            return EXIT_FAILURE;
        }

    }

    if(files.size() == 0) {
        std::cout << "No input files!" << std::endl;
        return EXIT_FAILURE;
    }

}