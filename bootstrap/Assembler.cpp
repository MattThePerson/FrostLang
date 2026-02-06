#include "Assembler.hpp"

#include <string>

//
std::string _get_text_buffer_template() {
    return R"(

    global _start

; --------------------------------------------------------------------------------
; | TEXT SECTION
; --------------------------------------------------------------------------------
    SECTION .text
_start:
    call main
    mov     rdi, rax ; move exit code for main
    mov     rax, 60 ; syscall for exit
    ;xor     rdi, rdi
    syscall

)";
}

//
std::string _get_exit_assembly_lines() {
    return R"(

_exit:
    mov     rax, 60 ; syscall for exit
    xor     rdi, rdi
    syscall

)";
}

//
std::string _get_data_buffer_template() {
    return R"(

; --------------------------------------------------------------------------------
; | DATA SECTION
; --------------------------------------------------------------------------------
    SECTION .data
)";
}

//
std::string _get_bss_buffer_template() {
    return R"(

; --------------------------------------------------------------------------------
; | BSS SECTION
; --------------------------------------------------------------------------------
    SECTION .bss
)";
}

std::string assemble(ASTNode) {

    std::string text_buffer = _get_text_buffer_template();
    std::string data_buffer = _get_data_buffer_template();
    std::string bss_buffer = _get_bss_buffer_template();
    std::string rodata_buffer; // for constants (perhaps later)

    /*
     * ind main() { io.print("Hello there\n"); return 0 }
     *
     * TOKEN:
     * ind
     * main
     * (
     * )
     * {
     * print
     * (
     * "
     * Hello there
     * \n
     * "
     * )
     * ;
     * return
     * 0
     * ;
     * }
     *
     * */

    // fill in buffers using AST
    // NOTE: Temp hello world
    text_buffer += "\nmain:";
    text_buffer += "\nmov rax, 1 ; syscall for write";
    text_buffer += "\nmov rdi, 1 ; flag for stdout";
    text_buffer += "\nmov rsi, MSG";
    text_buffer += "\nmov rdx, 35";
    text_buffer += "\nsyscall";
    text_buffer += "\nxor rax, rax";
    text_buffer += "\nret\n";

    data_buffer += "MSG: db \"Hello there, from assemble func!\", 10, 0\n";

    // append exit logic and concat buffers
    text_buffer += _get_exit_assembly_lines();
    std::string asm_src = text_buffer + data_buffer + bss_buffer;

    return asm_src;
}
