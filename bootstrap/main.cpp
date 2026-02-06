#include "Assembler.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"

#include <format>
#include <fstream>
#include <iostream>
// #include <vector>

int main(int argc, char *argv[]) {

    char asm_fn[] = "main.asm";
    char object_fn[] = "main.o";
    char binary_fn[] = "a.out";

    std::ifstream file_input;  // reading main.fro, main.thw
    std::ofstream file_output; // writing main.thw, main.asm

    // Ensure CL args
    if (argc == 1) {
        std::cerr << "error: no arguments passed dumbass\n";
    }

    // open file as stream
    file_input.open((argv[1]));
    if (!file_input) {
        std::cerr << "error: file could not be opened\n";
        return 1;
    }

    // STEP 1: lexing
    auto tokens = tokenize(file_input);
    file_input.close();

    // // TEMP: print tokens
    // std::cout << "TOKENS:\n";
    // int i = 0;
    // for (std::string token : tokens) {
    //     std::printf("%d: '%s'\n", ++i, token.c_str());
    // }
    // return 0;

    // STEP 2: generating AST
    ASTNode root_node;

    // STEP 3: generating assembly file
    std::string assembly_src = assemble(root_node);

    // STEP 4: write assembly to file
    // std::ofstream output_file(asm_fn);
    file_output.open(asm_fn);
    file_output.write(assembly_src.c_str(), assembly_src.length());
    file_output.close();

    // STEP 5: assemble and link
    int rc;
    std::string cmd;

    bool skip_assemble = false;
    bool skip_linking = false;

    // assemble (nasm)
    if (skip_assemble) {
        return 0;
    }
    cmd = std::format("nasm -felf64 {} -o {}", asm_fn, object_fn);
    rc = std::system(cmd.c_str());
    if (rc != 0) {
        // error
    }

    // link (ld)
    if (skip_linking) {
        return 0;
    }
    cmd = std::format("ld {} -o {}", object_fn, binary_fn);
    rc = std::system(cmd.c_str());
    if (rc != 0) {
        // error
    }

    return 0;
}
