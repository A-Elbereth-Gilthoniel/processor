# Proccessor and Assembler
## General information
 This program simulates the operation of a processor: the conversion of assembly language instructions into machine code, and their direct execution.

This program utilizes a code generation approach. This program simulates stack-based operations.

The program also simulates the dynamic memory and register behavior.

## Program start

Go to directory **./proccessor/** and enter the command in the console:

```C
>>> mingw32-make -f makeASM         // calling a makefile
>>> ./asmblr.exe factorial.txt      // calling .exe file.
//A text file containing assembly code is specified as the argument.
>>> mingw32-make -f makeCPU
>>> ./proc.exe
```

Additional commands:

```C
mingw32-make -f makeCPU clean       // cleaning ./CPU/obj/
mingw32-make -f makeASM clean       // cleaning ./ASM/obj/
```

## EXAMPLE

it is a content of 'factorial.txt'

```ASM
jmp main

Fact:
        push cx
        push bx
        mul
        pop cx
        push bx
        push 1
        add
        pop bx
        push bx
        push ax
        jae Contin
        ret
Contin:
        call Fact
        ret

main:
        in
        pop ax
        push 1
        pop bx
        push 1
        pop cx
        call Fact

        push cx
        out
        hlt
```

This is output:

```C
6
>>> 720.000000
```
