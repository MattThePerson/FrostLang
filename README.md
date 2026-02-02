# FrostLang

A (toy) compiler for my (toy) language FrostLang! Intended for x86-64 NASM Linux machines. 


## About FrostLang

### Idea

The goal of my language is to be something inbetween assembly (NASM) and C, and possibly with better structs (similar to Go). The language would introduce minimal abstractions for being productive, such as do-while instead of while and for loops (at least at the start). Also, the language would be able to interface directly with the CPU registers, being ale to read registers into variables, etc. (this would make it highly platform specific). 

As an initial goal, I thought it would be fun to make a language which then implements its own compiler. I would write the initial (boostrap) compiler in C++, building in the necessary features required to build a compiler (I will learn what these necessary features are along the way) and then rewrite the compiler in FrostLang. 

### Usage

Hello world:

```cpp
main {
    pr "Hello, world!\n";
    return 0;
}
```

Little more complicated:

```cpp
#stdlink "io"
#stdlink "str"
#insert "src/helpers"
#link "src/tokenizer" tok

#replace

// stdarg is a struct with 

main (u8 argc, u8 *argv[]) -> u8 {

    pr "";
    return 0;
}
```



Compiling:

```sh
frostc -c main.frost  # compile into main.asm
```

### Stages

1. Compile into **.asm**
2. Assemble into **.o** file (with `nasm`)
3. Link into executable (with `ld`)


### frostc compile flags

| Flag | Description |
| -- | -- |
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


## About the repo

This repo contains the source code for the original bootstrap compiler (C++), the source code for the compiler written in FrostLang (main.frost and src/), unit tests for the compiler (C++), as well as some of the 

```
|-- assembly_checkpoints # intermediate unlinked assembly outputs
|-- bootstrap/  # bootstrap compiler (C++)
|-- share/      # language agnostic resources (eg. tokenizer definitions)
|-- src/        # FrostLang compiler source files
|-- tests/      # unit tests  (C++)for the compiler
|-- main.frost  # main entry to FrostLang self-written compiler
```

