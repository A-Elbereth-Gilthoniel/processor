#include "assembler.h"

//--------------------------------------------------------------------------

#define DEF_CMD(name, code, ...) \
if (string_cmptor(command, #name))\
    return (ELEM)code;

#define REGISTER(name, code) \
if (string_cmptor(command, #name))\
    return (ELEM)code;

//--------------------------------------------------------------------------

ELEM assembler_encoding(char* command)
{
#include "../general/commands.h"
#include "../general/registers.h"

    return (ELEM)ERR;
}

//---------------------------------------------------------------------------

#undef DEF_CMD
#undef REGISTER
