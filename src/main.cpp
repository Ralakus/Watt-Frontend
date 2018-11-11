#include <iostream>
#include <fstream>
#include <string>
#include <vector>

namespace Watt {
    constexpr const char version[] = "0.1.0";

    void print_version() {
        std::cout << "Watt frontend version " << Watt::version << std::endl; 
    }

    void print_help_base() {
        print_version();
        std::cout << "-h or --help to print help" << std::endl;
        std::cout << "-f or --file <file> to compile files" << std::endl;
        std::cout << "-v or --version for version info" << std::endl;
    }

    void print_help_exit(int return_val) {
        print_help_base();
        std::exit(return_val);
    }

}


int main(int argc, char* argv[]) {

    std::vector<std::string> args{argv + 1, argv + argc};

    if(args.size() == 0) {
        std::cout << "No arguments!" << std::endl;
        return EXIT_FAILURE;
    }

    std::vector<std::pair<std::string, std::string>> files;  // Filename, file contents

    enum class arg_parse_state {
        other, files
    } parse_state;

    for(const auto& arg : args) {

        if(arg=="-h" || arg=="--help") {
            parse_state = arg_parse_state::other;
            Watt::print_help_exit(EXIT_SUCCESS);
        } 

        else if (arg=="-f" || arg=="--file") {
            parse_state = arg_parse_state::files;
            continue;
        }

        else if(arg=="-v" || arg=="--version") {
            parse_state = arg_parse_state::files;
            Watt::print_version();
            return EXIT_SUCCESS;
        }

        else if(arg=="--live") {
            std::cout << "Live compilation is not supported yet" << std::endl;
            return EXIT_SUCCESS;
        }

        else if(parse_state == arg_parse_state::files) {
            std::ifstream file(arg);
            if(!file.is_open()) {
                std::cout << "Failed to open file: \"" << arg << "\"!" << std::endl;
                return EXIT_FAILURE;
            }
            files.emplace_back(std::make_pair(arg, std::string((std::istreambuf_iterator<char>(file)),
                                                                std::istreambuf_iterator<char>())));
        }

        else {
            parse_state = arg_parse_state::files;
            std::cout << "Invalid argument: \"" << arg << '\"' << std::endl;
            Watt::print_help_exit(EXIT_FAILURE);
        }

    }

    if(files.size() == 0) {
        std::cout << "No input files!" << std::endl;
        return EXIT_FAILURE;
    }

}