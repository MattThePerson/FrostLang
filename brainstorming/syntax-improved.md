# Syntax improvements

more difficult to implement

## Macros for printing

```cpp
!std "io"

uind main() {

    // useful macros for printing
    !p "Hello World!\n";
    !pl "Append new line";
    !pf "Int: %d, float: %.1f, string: %s\n", 13, 5.9, "message here";
    io.printf("Int: %d, float: %.1f, string: %s\n", 13, 5.9, "message here");

    // replaces lines with this:
    io.print("Hello World!\n");

    return 0;
}

```

## CPU api

```cpp
!std "CPU"

uind main() {

    // 
    ui64: rax = CPU.get_reg_val("rax");
    CPU.mov("rdi", 13);

    return 0;
}
```

