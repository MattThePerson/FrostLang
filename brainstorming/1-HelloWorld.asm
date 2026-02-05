; ==============================================================================
; Hello World in Assembly
; ==============================================================================

    global    _start
    section   .text
_start:  
    mov       rax, 1                  ; system call for write
    mov       rdi, 1                  ; file handle 1 is stdout
    mov       rsi, message            ; address of string to output
    mov       rdx, 13                 ; number of bytes
    syscall                           ; invoke operating system to do the write
    mov       rax, 60                 ; system call for exit
    xor       rdi, rdi                ; exit code 0
    syscall                           ; invoke operating system to exit

    section   .data
message:
    db        "Hello, World", 10

; ==============================================================================
; FrostLang hello world with puts
; ==============================================================================

#ASM
    SECTION .bss
MESSAGE:
    db      $(MSG), 0

    global _start

    SECTION .text
_start:

; INPUTS:
;   rsi -> msg_addr
;   rdx -> msg_len
#ENDASM

;.print:
;    mov     rdx, $(MSG_LEN)
;    mov     rax, 1 ; write syscall
;    mov     rdi, 1 ; stdout
;    mov     rsi, MESSAGE
;    syscall

print("Hello world");

#ASM
.exit:
    mov     rax, 60
    xor     rdi, rdi
    syscall
#ENDASM
