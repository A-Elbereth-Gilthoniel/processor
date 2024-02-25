#include "processor.h"

//---------------------------------------------------------

void make_ram(cpu* handler)
{
    int size = 100;
    handler->ram = (ELEM*) calloc(size, sizeof(ELEM));
}

//--------------------------------------------------------

