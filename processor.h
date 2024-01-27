#ifndef PROCESSOR_H
#define PROCESSOR_H

//#define CANARY
//#define DUMP

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>

typedef double ELEM;
#define SPEC "%lf"

#ifdef CANARY
typedef long long CANARY_TYPE;
//const CANARY_TYPE CANARY_NUMBER = 0xDEADDEAD;
#endif



#define red(str) "\033[31m"#str"\033[0m"

#define new_assert(expr) {\
    fprintf(stderr, red(There is error) ": File: %s, Function: %s, Line: %d, Error :  \"%s\"\n", __FILE__, __func__, __LINE__, expr);\
    exit(1);\
}

#define stack_assert(expr) if (expr != "NO_ERRORS"){\
    fprintf(stderr, red(There is error) ": File: %s, Function: %s, Line: %d, Error :  \"%s\"\n", __FILE__, __func__, __LINE__, expr);\
    exit(1);\
}

enum ASSEMBLER_COMMANDS {
    PUSH = 1,
    OUT = 2,
    POP = 3,
    IN = 4,
    HLT = 5,
    MUL = 6,
    ADD = 7,
    SUB = 8,
    DIV = 9,
    JMP = 10,
    JB = 11,
    JBE = 12,
    JA = 13,
    JAE = 14,
    JE = 15,
    JNE = 16,
    CALL = 17,
    RET = 18,
    RPUSH = 19,
    AX = 100,
    BX = 101,
    CX = 102,
    DX = 103
};

enum CODE_ERROR {
    NO_ERRORS,
    STACK_ERR,
    STACK_IS_UNDECLARED,
    SIZE_LESS_THAN_ZERO,
    CAPACITY_LESS_THAN_ZERO,
    SIZE_MORE_THAN_CAPACITY,
    BOTH_CANARIES_DIED,
    LEFT_CANARY_DIED,
    RIGHT_CANARY_DIED
};


typedef struct stack {
    ELEM* data;
    int size ;
    int capacity;

    #ifdef CANARY
    CANARY_TYPE* left_canary;
    CANARY_TYPE* right_canary;
    #endif
} STACK;

typedef struct list {
    ELEM* massive_of_code;
    int size;
    ELEM* tag_massive;
    int* tag_indexs;
    int tag_number;
} COMMAND_LIST;


void StackConstructor(STACK *st, const size_t length);
void StackPush(STACK* st, ELEM value);
void StackDestructor(STACK* st);
ELEM StackPop(STACK* st);
void PrintStack(STACK* st);
void StackRealloc(STACK *st, const int size);
char* StackVerification(STACK *st);
void assembler_reading(COMMAND_LIST *commands);
size_t find_file_size(FILE* fp);
/*int fill_massive_of_code(COMMAND_LIST *commands, size_t number_of_symbols, char* from);*/
int fill_massive_of_code(COMMAND_LIST *commands, size_t number_lines, char* from);
int only_numeric_symbols(char* buffer, size_t size_buffer);
int cmp_with_number(ELEM number1, ELEM number2);
ELEM assembler_encoding(char* command);
void clear_char_massive(char* massive, int size);
int string_cmptor(char* str1, char* str2);
void PutChar(char c);
void disassembler(ELEM* massive_of_code, size_t size);
void do_pop(STACK *stk, ELEM data, ELEM* ax, ELEM* bx, ELEM* cx, ELEM* dx);
void do_jump(COMMAND_LIST *commands, int *cur_ind);
void put_into_file(ELEM* massive_of_code, size_t size);
int find_number_lines(char* string);
char* r_replace(char *orig, int size);
char* n_replace(char *orig, int size);
#ifdef DUMP
void StackDump(STACK *st, const char* file, const char* func);
#endif

#endif    // PROCESSOR_H
