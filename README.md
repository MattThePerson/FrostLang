# FrostLang

A (toy) compiler for my (toy) language FrostLang! Intended for x86-64 NASM Linux machines. 


## About FrostLang

### Idea

The goal of my language is to be something inbetween assembly (NASM) and C, and possibly with better structs (similar to Go). The language would introduce minimal abstractions for being productive, such as do-while instead of while and for loops (at least at the start). Also, the language would be able to interface directly with the CPU registers, being ale to read registers into variables, etc. (this would make it highly platform specific). 

As an initial goal, I thought it would be fun to make a language which then implements its own compiler. I would write the initial (boostrap) compiler in C++, building in the necessary features required to build a compiler (I will learn what these necessary features are along the way) and then rewrite the compiler in FrostLang. 

### Usage

Compiling:

```sh
frostc -S main.frost  # compile into main.asm
```

### Stages

1. Preprocess into **.thaw** file
2. Compile into **.asm**
3. Assemble into **.o** file (with `nasm`)
4. Link into executable (with `ld`)


### frostc compile flags

| Flag | Description |
| -- | -- |
| `-P` | Preprocess (produce .thaw file) |
| `-S` | Compile to assembly file |
| `-A` | Assemble to object file (uses nasm) |
| `-L` | Link object file (uses ld) |
| `--run` | Fully compile then run executable |




### gcc compile flags

| Flag | Description |
| -- | -- |
| `-E` | Only preprocess (.i files) |
| `-S` | Stop after compilation (symbolic machine code, assembly) |
| `-c` | Object file, dont link |
| none | All |


### Examples

Hello world:

```cpp
i main {
    pr "Hello, world!\n";
    return 0;
}
```

Little more complicated:

```cpp
!stdlink "io"  // link 
!stdlink "fmt"

!link "src/tokenizer"

!inject (
    "libfrosty/io"
    "libfrosty/strfmt"
)
!inject "src/helpers"  // directly injects code here

!replace "idef" "i64"
!replace "udef" "u64"
!replace "fdef" "f64"

// stdarg is a struct with 


namespace IO {
    obj args {
        u64 length;
    u8[] argv;
    }
}

_ helper(u8 a, f32 b) {

}

i32 main {

    // reading CL args
    args.args[2];
    args.length;
    prf "%d hello %f", a, b;

    // file reading
    io.ifile file;
    file.open("example.txt");
    u8 ch = file.read_next_char();
    while (ch != io.EOF) {
        // ...
    } {ch = file.read_next_char()}

    // for loop
    ivar i;
    fvar u;
    uvar u;
    while (i < 5) {
        // do stuff
    } {i++}


    return 0;
}
```

Assembly proximity in Frosty:

```cpp
!import "CPU"

i32 main {

    // inject assembly
    #ASM NASM_x86-64
    mov       rdi, 1
    mov       rsi, message
    mov       rdx, 13
    syscall
    mov       rax, 60
    xor       rdi, rdi
    syscall
    #ENDASM

    // read and write registers using CPU API
    u64 rgi = CPU.read_reg("rdi");
    CPU.mov("rsi", 13);
    CPU.xor("rdi", "rdi");
    CPU.syscall();

    // single line of assembly
    #ASML mov rsi, 13;

    !pr "Hello world!\n";                       // print macro
    
    !prf "Value: %d\n", 13;                     // printf macro
    print(string.format("Value: %d\n", 13));    // what the above expands to 

    return 0;
}

```



## About the repo

This repo contains the source code for the original bootstrap compiler (C++), the source code for the compiler written in FrostLang (main.frost and src/), unit tests for the compiler (C++), as well as some of the 


The directory structure is 

```
|-- ass_ckpts/      # intermediate unlinked assembly outputs
|-- bin/            # binaries
|-- bootstrap/      # bootstrap compiler (C++)
|-- libfrosty/      # Frosty standard libraries
|-- src/            # FrostLang compiler source files
|   |-- Parser.fro
|   |-- Lexer.fro
|-- unit_tests/          # unit tests  (C++)for the compiler
|-- main.fro        # main entry to FrostLang self-written compiler
```
.fy
.fs
.fro

### Compiling boostrap (C++) compiler

Build with `cmake`. cd into bootstrap/, then:

- `mkdir build && cd build`
- `cmake ..`
- `cmake --build .`

This will create `frostc_cpp` into bin/. 
