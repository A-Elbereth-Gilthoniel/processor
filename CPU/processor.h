#define PROCESSOR_H
#ifdef PROCESSOR_H

#include "../general/libr.h"

//#define DUMP


enum CODE_ERROR {
    NO_ERRORS,
    STACK_ERR,
    STACK_IS_UNDECLARED,
    SIZE_LESS_THAN_ZERO,
    CAPACITY_LESS_THAN_ZERO,
    SIZE_MORE_THAN_CAPACITY,
};


typedef struct stack {
    ELEM* data;
    int size ;
    int capacity;
} STACK;

typedef struct list {
    ELEM* massive_of_code;
    ELEM* ram;
    int size;
    int* tag_indexs;
    int tag_number;
    STACK data_stk;
    STACK adress_stk;
} cpu;


void StackConstructor(STACK *st, const size_t length);
void StackPush(STACK* st, ELEM value);
void StackDestructor(STACK* st);
ELEM StackPop(STACK* st);
void PrintStack(STACK* st);
void StackRealloc(STACK *st, const int size);
char* StackVerification(STACK *st);
void cpu_destr(cpu* handler);
int only_numeric_symbols(char* buffer, size_t size_buffer);
int cmp_with_number(ELEM number1, ELEM number2);
void work_with_bin_file(cpu* handler);
void do_commands(cpu *handler);
void make_ram(cpu* handler);
void StackDump(STACK *st, const char* file, const char* func);

#endif    // PROCESSOR_H
