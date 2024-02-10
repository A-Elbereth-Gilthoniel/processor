#include "assembler.h"

//----------------------------------------------------------------------------

int only_numeric_symbols(char* buffer, size_t size_buffer)  // Checking that only a number is entered
{
    if (size_buffer == 0)
        return 0;
    int number_of_points = 0;
    for (int i = 0; i < size_buffer; i++)
    {
        if (buffer[i] == '.' && i != 0 && number_of_points == 0 && i != size_buffer - 1)
            number_of_points++;
        if ((!isdigit(buffer[i])) && ((buffer[i] != '-' || size_buffer == 1)|| i != 0))
            return 0;
    }
    return 1;
}

//------------------------------------------------------------------------------

int cmp_with_number(ELEM number1, ELEM number2)
{
    const double eps = 1e-5;

    return number2 - eps <= number1 && number1 <= number2 + eps;
}

//------------------------------------------------------------------------------

int check_tag_existing(char** tag_names, char* middle_buffer, int tag_number)
{
    for (int j = 0; j < tag_number; j++)
    {
        if (string_cmptor(tag_names[j], middle_buffer) == 1)
        {
            return j;
        }
    }
    return -1;
}

//-------------------------------------------------------------------

#define REGISTER(name, code) if (string_cmptor(cur_com, #name)) \
{\
no_ram_err = 1;\
cur_cmd_is_reg = 1;\
}

#define DEF_CMD(name, code, arg, ...) if ((int)last_cmd_code == code) \
{\
last_cmd_arg_num = arg; \
}

void asm_verification(char* last_com, char* cur_com, ELEM cur_cmd_code, int* is_ram)
{
    int last_cmd_arg_num = 0;
    int cur_cmd_is_reg = 0;
    ELEM last_cmd_code = assembler_encoding(last_com);
    int cur_cmd_is_num = only_numeric_symbols(cur_com, strlen(cur_com));
    int last_cmd_is_num = only_numeric_symbols(last_com, strlen(last_com));

    int no_ram_err = 0;
#include "registers.h"

    if ((int)last_cmd_code == ERR && last_cmd_is_num == 0 && (cur_cmd_is_num == 1 || cur_cmd_is_reg == 1))
    {
        fprintf(stderr, red(Error)": Instead of a command at the beginning, a number or a register: '%s'", cur_com);
        exit(1);
    }

    if ((string_cmptor("push", last_com) || string_cmptor(last_com, "pop")) && *(is_ram) == 1)
    {

        if (cur_cmd_is_num) no_ram_err = 1;

        if (no_ram_err == 0)
        {
            fprintf(stderr, red(Error)": Undefined adress to RAM: %s [%s]", last_com, cur_com);
            exit(1);
        }
    }

    if (cur_cmd_is_num == 0 && (int)cur_cmd_code == ERR)
    {
        fprintf(stderr, red(Error)": There is unknown tag in the code: %s", cur_com);
        exit(1);
    }

    if (cur_cmd_is_num == 0 && last_cmd_is_num == 0 && cur_cmd_is_reg == 0)
    {
#include "commands.h"
        if (last_cmd_arg_num > 0)
        {
            fprintf(stderr, red(Error)": Not enough arguments for command '%s'", last_com);
            exit(1);
        }
    }

    *(is_ram) = 0;
}

#undef DEF_CMD
#undef REGISTER

//-------------------------------------------------------------------------

void tag_verification(char** tag_names, int* tag_indexs, int tag_number)
{
    for (int i = 0; i < tag_number; i++)
    {
        if (tag_indexs[i] == -1)
        {
            fprintf(stderr, red(Error)": There is no link for the label '%s'", tag_names[i]);
            exit(1);
        }
    }
}

//-------------------------------------------------------------------------
