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
    fprintf(stdout, "new command: %s\n", command);
#include "commands.h"
#include "registers.h"


    new_assert("There is unknown command in .txt file: %s", command);
}

//---------------------------------------------------------------------------

#undef DEF_CMD
#undef REGISTER
