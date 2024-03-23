#include "processor.h"


void StackConstructor(STACK *st, const size_t length)
{
    st->data = (ELEM*) calloc(length, sizeof(ELEM));

    st->capacity = length;
    st->size = 0;

    stack_assert(StackVerification(st));
    StackDump(st, "stack.c", "StackConstructor");
}

//--------------------------------------------------------------------------

void StackPush(STACK* st, ELEM value)
{
    if (st->size == st->capacity)
    {
        StackRealloc(st, st->capacity * 2);
    }
    st->data[st->size++] = value;

    StackDump(st, "stack.c", "StackPush");
    stack_assert(StackVerification(st));
}

//---------------------------------------------------------------------------

void StackDestructor(STACK* st)
{
    free(st->data);
    st->data = NULL;
    st->size = 0;
    st->capacity = 0;
    StackDump(st, "stack.c", "StackDestructor");
}

//----------------------------------------------------------------------------

ELEM StackPop(STACK* st)
{
    ELEM last_elem = st->data[st->size - 1];
    st->data[st->size - 1] = 0;
    st->size--;

    if (st->size < st->capacity / 3)
    {
        StackRealloc(st, (st->capacity / 3)+1);
    }

    StackDump(st, "stack.c", "StackPop");

    stack_assert(StackVerification(st));
    return last_elem;
}

//----------------------------------------------------------------------------

void PrintStack(STACK* st)
{
    for (int i = 0; i < st->size; i++)
        printf(SPEC" ", st->data[i]);
    printf("\n");
}

//----------------------------------------------------------------------------

void StackRealloc (STACK *st, const int new_capacity)
{
    st->data = (ELEM *) realloc (st->data, (new_capacity + 1) * sizeof(ELEM));
    int dogon = 0;

    if (new_capacity - st->capacity > 0)
    {
        memset (st->data + st->capacity + dogon, 0, (new_capacity - st->capacity) * sizeof (ELEM));
    }

    st->capacity = new_capacity;

    StackDump(st, "stack.c", "StackRealloc");

    stack_assert(StackVerification(st));
}

//----------------------------------------------------------------------------

char* StackVerification(STACK *st)
{
    if (st == NULL)
        return "STACK_IS_UNDECLARED";
   /* if (st->data == NULL)
        return "STACK_IS_UNDECLARED";*/
    if (st->size < 0)
        return "SIZE_LESS_THAN_ZERO";
    if (st->capacity < 0)
        return "CAPACITY_LESS_THAN_ZERO";
    if (st->size > st->capacity)
        return "SIZE_MORE_THAN_CAPACITY";
    else
        return "NO_ERRORS";
}

//----------------------------------------------------------------------------

void StackDump(STACK *st, const char* file, const char* func)
{
    #ifdef DUMP
    printf("File: %s\nFunction: %s\n", file, func);
    printf("Capacity: %d\nsize: %d\n", st->capacity, st->size);

    for (int i = -1; i < st->capacity+1; i++)
    {
        printf("[%d]: "SPEC"\n", i, st->data[i]);
    }

    printf("===========================\n");
    #endif
}
