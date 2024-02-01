#define PROCESSOR_H
#ifdef PROCESSOR_H

#include "libr.h"

//#define CANARY
//#define DUMP

#ifdef CANARY
typedef long long CANARY_TYPE;
//const CANARY_TYPE CANARY_NUMBER = 0xDEADDEAD;
#endif


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
   // ELEM* tag_massive;
    int* tag_indexs;
    int tag_number;
    STACK data_stk;
    STACK adress_stk;
} COMMAND_LIST;


void StackConstructor(STACK *st, const size_t length);
void StackPush(STACK* st, ELEM value);
void StackDestructor(STACK* st);
ELEM StackPop(STACK* st);
void PrintStack(STACK* st);
void StackRealloc(STACK *st, const int size);
char* StackVerification(STACK *st);
int only_numeric_symbols(char* buffer, size_t size_buffer);
int cmp_with_number(ELEM number1, ELEM number2);
ELEM assembler_encoding(char* command);
void do_pop(STACK *stk, ELEM data, ELEM* ax, ELEM* bx, ELEM* cx, ELEM* dx);
void do_jump(COMMAND_LIST *commands, int *cur_ind);
void work_with_bin_file(COMMAND_LIST* commands);
void do_commands(COMMAND_LIST *commands);
#ifdef DUMP
void StackDump(STACK *st, const char* file, const char* func);
#endif

#endif    // PROCESSOR_H
