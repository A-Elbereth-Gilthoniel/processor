#include "processor.h"

int main()
{
    cpu handler;
    make_ram(&handler);
    work_with_bin_file(&handler);
    StackConstructor(&handler.data_stk, 50);
    StackConstructor(&handler.adress_stk, 50);
    do_commands(&handler);
    cpu_destr(&handler);
}

//-----------------------------------------------------------

void cpu_destr(cpu* handler)
{
    free(handler->massive_of_code);
    free(handler->tag_indexs);
    free(handler->ram);
    StackDestructor(&handler->adress_stk);
    StackDestructor(&handler->data_stk);
}

//------------------------------------------------------------
