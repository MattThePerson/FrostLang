# FrostLang

A (toy) compiler for my (toy) language FrostLang! Intended for x86-64 NASM Linux machines. 

## Idea

The goal of my language is to be something inbetween assembly (NASM) and C, and possibly with better structs (similar to Go). The language would introduce minimal abstractions for being productive, such as do-while instead of while and for loops (at least at the start). Also, the language would be able to interface directly with the CPU registers, being ale to read registers into variables, etc. (this would make it highly platform specific). 

As an initial goal, I thought it would be fun to make a language which then implements its own compiler. I would write the initial (boostrap) compiler in C++, building in the necessary features required to build a compiler (I will learn what these necessary features are along the way) and then rewrite the compiler in FrostLang. 

## Usage

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


