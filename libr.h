#include <stdio.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>


typedef double ELEM;
#define SPEC "%lf"

#define red(str) "\033[31m"#str"\033[0m"

#define new_assert(expr) {\
    fprintf(stderr, red(There is error) ": File: %s, Function: %s, Line: %d, Error :  \"%s\"\n", __FILE__, __func__, __LINE__, expr);\
    exit(1);\
}

#define stack_assert(expr) if (expr != "NO_ERRORS"){\
    fprintf(stderr, red(There is error) ": File: %s, Function: %s, Line: %d, Error :  \"%s\"\n", __FILE__, __func__, __LINE__, expr);\
    exit(1);\
}

/*#define asmblr_assert(expr) if (expr != "NO_ERRORS){\


}*/

enum ASSEMBLER_COMMANDS {
    SPACE =  0,
    PUSH  =  1,
    OUT   =  2,
    POP   =  3,
    IN    =  4,
    HLT   =  5,
    MUL   =  6,
    ADD   =  7,
    SUB   =  8,
    DIV   =  9,
    JMP   =  10,
    JB    =  11,
    JBE   =  12,
    JA    =  13,
    JAE   =  14,
    JE    =  15,
    JNE   =  16,
    CALL  =  17,
    RET   =  18,
    RPUSH =  19,
    AX    = 100,
    BX    = 101,
    CX    = 102,
    DX    = 103
};
