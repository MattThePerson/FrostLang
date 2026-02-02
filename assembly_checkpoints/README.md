# Assembly Checkpoints

Intermediate assembly checkpoints for C++ or native FrostLang compiler. I have sought to preserve some notable versions here incase every clang and gcc binary gets accidentally deleted. 

## About

Because FrostLang only supports x86-64 intel style NASM assembly, the assembly output of the compilation process (either bootstrap or native) also uniquely represents the final compiler goal, and can thus be used to produce the compiler without any dependencies, other than nasm and ld.

All you need to do is assemble and link the file:

```sh
nasm -felf64 frostc-*.asm -o frostc-*.o
ld frostc-*.o -o frostc-*
```
