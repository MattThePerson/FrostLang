# Simple syntax


## Types

defaults:
- ind -> int default (32 bit)
- uind & fld

explicit:
- in64 in32 in16 in8
- fl64 fl32 fl16 fl8
- uin64 uin32 uin16 uin8
- vd (void)


## 

```cpp
// set env variable $FROSTY_STDLIB_PATH="..." used by !std
!std "io"
!inject "src/thing"

uind main() {

    
    return 0;
}
```


## Injecting Assembly

```cpp
/*
 * Injecting assembly: get added as unprocessed tokens
 */
uind main() {

    // multilines
    #ASM x64_NASM
    add     rdi, rsi
    mov     rax, 69
    ret
    #ENDASM

    // singleline
    #ASML xor rax, rax ; // must end with semicolon

    return 0;
}
```

