//#include "processor.h"
#include "assembler.h"

//------------------------------------------------------------

static const int MAX_CMD_NUM = 23;

char* command_array[MAX_CMD_NUM] = {"push", "out", "pop", "in", \
                                    "hlt", "mul", "add", "sub", \
                                    "div", "jmp", "jb", "jbe",  \
                                    "ja", "jae", "je", "jne",   \
                                    "call", "ret", "rpush",     \
                                    "ax", "bx", "cx", "dx"}

//------------------------------------------------------------

ELEM assembler_encoding(char* command)
{
    for (int i = 0; i < MAX_CMD_NUM; i++)
        if (string_cmptor(command, command_array[i]))
            return (ELEM)(i + 1);

    new_assert(("Unknown command: %s", command));
}

//---------------------------------------------------------------------------
