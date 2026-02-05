#include <fstream>
#include <iostream>
#include <vector>

#include "Lexer.hpp"

// This program reads values from a file passed as argument 1
int main(int argc, char *argv[]) {

    // Ensure CL args
    if (argc == 1) {
        std::cerr << "error: no arguments passed dumbass\n";
    }

    // open file as stream
    std::ifstream input_file(argv[1]); // instream is like cin
                                       // input_file.open(argv[1]);
    if (!input_file) {
        std::cerr << "error: file could not be opened\n";
        return 1;
    }

    // step 1: lexing
    std::vector<std::string> tokens = tokenize(input_file);
    input_file.close();

    // NOTE: Temporary
    std::cout << "TOKENS:\n";
    int i = 0;
    for (std::string token : tokens) {
        // std::cout << ++i << ": " << token << std::endl;
        std::printf("%d: '%s'\n", ++i, token.c_str());
    }

    // // print vector
    // std::string s{charvect.begin(), charvect.end()};
    // std::cout << "string: " << s << std::endl;

    // // write to file
    // std::ofstream output_file("file_out.txt");
    // output_file << s;
    // output_file.close();

    return 0;
}
