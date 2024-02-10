#include "processor.h"

int main()
{
    COMMAND_LIST commands;
    make_ram(&commands);
    work_with_bin_file(&commands);
    StackConstructor(&commands.data_stk, 50);
    StackConstructor(&commands.adress_stk, 50);
    do_commands(&commands);
    free(commands.massive_of_code);
    free(commands.tag_indexs);
    free(commands.ram);
}
