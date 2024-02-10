#include "processor.h"

//---------------------------------------------------------

void make_ram(COMMAND_LIST* commands)
{
    int size = 100;
    commands->ram = (ELEM*) calloc(size, sizeof(ELEM));
}

//--------------------------------------------------------

