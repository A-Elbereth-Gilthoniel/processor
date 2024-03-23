#include "processor.h"

//-------------------------------------------------------------

#define DEF_CMD(name, code, arg_num, program)   \
case code:                                      \
    program                                     \
    cur_ind = cur_ind + 1 + (arg_num);          \
    break;

#define REGISTER(name, code) fprintf(stdout, #name" = "SPEC", ", registers[code - 100]);

#include "../general/DSL.h"

//------------------------------------------------------------------------------

void do_commands(cpu *handler)
{
    ELEM registers[REG_NUM] = {};

    ELEM middle_number = 0, middle_number2 = 0;
    ELEM number = 0;
    int cur_ind = 0, tag_exist = 0;
    while (cur_ind < handler->size)
    {
        switch ((int)handler->massive_of_code[cur_ind])
        {
#include "../general/commands.h"
            default:
                tag_exist = 0;
                for (int i = 0; i < handler->tag_number; i++)
                {
                    if (1000 + i == (int)handler->massive_of_code[cur_ind])
                    {
                        tag_exist++;
                        cur_ind++;
                        tag_exist = 1;
                        break;
                    }
                }
                if (tag_exist == 0)
                {
                    new_assert("There is unknown tag");

                }
        }
    }
//#include "../general/registers.h"
}

//---------------------------------------------------------------------

#undef DEF_CMD
#undef REGISTER
