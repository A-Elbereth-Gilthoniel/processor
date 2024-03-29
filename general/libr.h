#include <stdio.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>


typedef double ELEM;
#define SPEC "%lf"

#define red(str) "\033[31m"#str"\033[0m"

#define REG_NUM 4

#define new_assert(expr) \
    fprintf(stdout, red(Error)": %s\n", expr);\
    exit(1);

#define stack_assert(expr) if (expr != "NO_ERRORS"){\
    fprintf(stderr, red(There is error) ": File: %s, Function: %s, Line: %d, Error :  \"%s\"\n", __FILE__, __func__, __LINE__, expr);\
    exit(1);\
}


#define REGISTER(name, code) REG_##name = code,

enum ASSEMBLER_REGISTERS {
    #include "registers.h"
    ASM = -1
};

#undef REGISTER

#define DEF_CMD(name, code, ...) name = code,

enum ASSEMBLER_COMMANDS {
    #include "commands.h"
    ERR = -1
};

#undef DEF_CMD
