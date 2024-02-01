//#include "processor.h"
#include "assembler.h"

//------------------------------------------------------------

/*static const int MAX_CMD_NUM = 23;

char* command_array[MAX_CMD_NUM] = {"push", "out", "pop", "in", \
                                    "hlt", "mul", "add", "sub", \
                                    "div", "jmp", "jb", "jbe",  \
                                    "ja", "jae", "je", "jne",   \
                                    "call", "ret", "rpush",     \
                                    "ax", "bx", "cx", "dx"};*/

//------------------------------------------------------------


#define DEF_CMD(name, code, ...) \
if (string_cmptor(command, #name))\
    return (ELEM)code;

#define REGISTER(name, code) \
if (string_cmptor(command, #name))\
    return (ELEM)code;

//-----------------------------------------------------

ELEM assembler_encoding(char* command)
{
    fprintf(stdout, "new command: %s\n", command);
#include "commands.h"
#include "registers.h"


    new_assert(("Unknown command: %s", command));
}

//---------------------------------------------------------------------------

#undef DEF_CMD
#undef REGISTER
