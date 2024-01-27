#include "processor.h"

//------------------------------------------------------------

/*static const int MAX_CMD_NUM = 23;

char* command_array[MAX_CMD_NUM] = {"push", "out", "pop", "in", \
                        "hlt", "mul", "add", "sub", \
                        "div", "jmp", "jb", "jbe", \
                        "ja", "jae", "je", "jne", \
                        }*/

//------------------------------------------------------------

ELEM assembler_encoding(char* command)
{
    if (string_cmptor(command, "push"))
        return (ELEM)1;
    if (string_cmptor(command, "out"))
        return (ELEM)2;
    if (string_cmptor(command, "pop"))
        return (ELEM)3;
    if (string_cmptor(command, "in"))
        return (ELEM)4;
    if (string_cmptor(command, "hlt"))
        return (ELEM)5;
    if (string_cmptor(command, "mul"))
        return (ELEM)6;
    if (string_cmptor(command, "add"))
        return (ELEM)7;
    if (string_cmptor(command, "sub"))
        return (ELEM)8;
    if (string_cmptor(command, "div"))
        return (ELEM)9;
    if (string_cmptor(command, "jmp"))
        return (ELEM)10;
    if (string_cmptor(command, "jb"))
        return (ELEM)11;
    if (string_cmptor(command, "jbe"))
        return (ELEM)12;
    if (string_cmptor(command, "ja"))
        return (ELEM)13;
    if (string_cmptor(command, "jae"))
        return (ELEM)14;
    if (string_cmptor(command, "je"))
        return (ELEM)15;
    if (string_cmptor(command, "jne"))
        return (ELEM)16;
    if (string_cmptor(command, "call"))
        return (ELEM)17;
    if (string_cmptor(command, "ret"))
        return (ELEM)18;
    if (string_cmptor(command, "rpush"))
        return (ELEM)19;
    if (string_cmptor(command, "ax"))
        return (ELEM)100;
    if (string_cmptor(command, "bx"))
        return (ELEM)101;
    if (string_cmptor(command, "cx"))
        return (ELEM)102;
    if (string_cmptor(command, "dx"))
        return (ELEM)103;
    new_assert(("Unknown command: %s", command));
}

//---------------------------------------------------------------------------
