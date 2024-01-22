#include "processor.h"

//--------------------------------------------

void do_pop(STACK *stk, ELEM data, ELEM* ax, ELEM* bx, ELEM* cx, ELEM* dx)
{
    ELEM number = StackPop(stk);
    switch ((int)data)
    {
        case AX:
            *ax = number;
            break;
        case BX:
            *bx = number;
            break;
        case CX:
            *cx = number;
            break;
        case DX:
            *dx = number;
            break;
        default:
            assert(NULL);
    }
}

//-------------------------------------------------------------

void do_jump(COMMAND_LIST *commands, int *cur_ind)
{
    for (int i = 0; i < commands->tag_number; i++)
    {
        if ((int)commands->tag_massive[i] == (int)commands->massive_of_code[*(cur_ind) + 1])
        {
           // fprintf(stdout, "index: %d\n", commands->tag_indexs[i]);
            *(cur_ind) = commands->tag_indexs[i] + 1;
            break;
        }
    }
}

//-------------------------------------------------------------
