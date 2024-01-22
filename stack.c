#include "processor.h"

#ifdef CANARY
CANARY_TYPE CANARY_NUMBER = -1111111111;
#endif

void StackConstructor(STACK *st, const size_t length)
{
    #ifdef CANARY
    st->data = (ELEM*) calloc(length + 2 * sizeof(CANARY_TYPE), sizeof(ELEM));
    #else
    st->data = (ELEM*) calloc(length, sizeof(ELEM));
    #endif


    st->capacity = length;
    st->size = 0;

    #ifdef CANARY

    *((CANARY_TYPE*)(st->data)) = CANARY_NUMBER;
    *((CANARY_TYPE*)(st->data + st->capacity + 1)) = CANARY_NUMBER;
    st->left_canary = (CANARY_TYPE*)(st->data-1);
    st->right_canary = ((CANARY_TYPE*)(st->data + st->capacity + 1));
    st->data++;


    #endif

    stack_assert(StackVerification(st));
    #ifdef DUMP
    StackDump(st, "stack.c", "StackConstructor");
    #endif
}

//--------------------------------------------------------------------------

void StackPush(STACK* st, ELEM value)
{
    if (st->size == st->capacity)
    {
        StackRealloc(st, st->capacity * 2);
    }
    st->data[st->size++] = value;

    #ifdef DUMP
    StackDump(st, "stack.c", "StackPush");
    #endif
    stack_assert(StackVerification(st));
}

//---------------------------------------------------------------------------

void StackDestructor(STACK* st)
{
    free(st->data);
    st->data = NULL;
    st->size = 0;
    st->capacity = 0;
    #ifdef DUMP
    StackDump(st, "stack.c", "StackDestructor");
    #endif
}

//----------------------------------------------------------------------------

ELEM StackPop(STACK* st)
{
    ELEM last_elem = st->data[st->size - 1];
    st->data[st->size - 1] = 0;
    st->size--;

    if (st->size < st->capacity / 3)
    {
       /* st->data = (ELEM*) realloc(st->data, (st->size + 1) * sizeof(ELEM));
        assert (st->data != NULL);
        st->capacity = st->size + 1;*/
        fprintf(stdout, "%d\n", st->capacity / 3);
        StackRealloc(st, (st->capacity / 3)+1);
    }

    #ifdef DUMP
    StackDump(st, "stack.c", "StackPop");
    #endif

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
    #ifdef CANARY
    st->data = (ELEM *) realloc ((st->data - 1), (new_capacity) * sizeof(ELEM) + 2 * sizeof(CANARY_TYPE));
    int dogon = 1;
    #else
    st->data = (ELEM *) realloc (st->data, (new_capacity + 1) * sizeof(ELEM));
    int dogon = 0;
    #endif

    if (new_capacity - st->capacity > 0)
    {
        memset (st->data + st->capacity + dogon, 0, (new_capacity - st->capacity) * sizeof (ELEM));
    }

    #ifdef CANARY
    *((CANARY_TYPE*)(st->data+new_capacity + 1)) = CANARY_NUMBER;
    st->data++;
   // st->right_canary = ((CANARY_TYPE*)(st->data+size));

    #endif

    st->capacity = new_capacity;

    #ifdef DUMP
    StackDump(st, "stack.c", "StackRealloc");
    #endif

    stack_assert(StackVerification(st));
}

//----------------------------------------------------------------------------

char* StackVerification(STACK *st)
{
    if (st == NULL)
        return "STACK_IS_UNDECLARED";
    if (st->data == NULL)
        return "STACK_IS_UNDECLARED";
    if (st->size < 0)
        return "SIZE_LESS_THAN_ZERO";
    if (st->capacity < 0)
        return "CAPACITY_LESS_THAN_ZERO";
    if (st->size > st->capacity)
        return "SIZE_MORE_THAN_CAPACITY";
    #ifdef CANARY
    if (st->data[-1] != CANARY_NUMBER && st->data[st->capacity] != CANARY_NUMBER)
        return "BOTH_CANARIES_DIED";
    if (st->data[-1] != CANARY_NUMBER)
        return "LEFT_CANARY_DIED";
    if (st->data[st->capacity] != CANARY_NUMBER)
        return "RIGHT_CANARY_DIED";

    #endif
    else
        return "NO_ERRORS";
}

//----------------------------------------------------------------------------

#ifdef DUMP
void StackDump(STACK *st, const char* file, const char* func)
{
    printf("File: %s\nFunction: %s\n", file, func);
    printf("Capacity: %d\nsize: %d\n", st->capacity, st->size);

    for (int i = -1; i < st->capacity+1; i++)
    {
        printf("[%d]: "SPEC"\n", i, st->data[i]);
    }

    #ifdef CANARY
    printf("LEFT CANARY: %lld\n", st->data[-1]);
    printf("RIGHT CANARY: %lld\n", st->data[st->capacity]);
    #endif

    printf("===========================\n");
}
#endif
