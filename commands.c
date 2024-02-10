#include "processor.h"

//-------------------------------------------------------------

#define DEF_CMD(name, code, arg_num, program)\
case code: \
    program \
    cur_ind = cur_ind + 1 + (arg_num); \
    printf("code = %d\n", code);\
    break;

#define REGISTER(name, code) fprintf(stdout, #name" = "SPEC", ", registers[code - 100]);

//------------------------------------------------------------------------------

void do_commands(COMMAND_LIST *commands)
{
    ELEM registers[REG_NUM] = {};
    for (int i = 0; i < commands->tag_number; i++)
        printf("%d  ", commands->tag_indexs[i]);
    ELEM middle_number = 0, middle_number2 = 0;
    ELEM number = 0;
    int cur_ind = 0, tag_exist = 0;
    while (cur_ind < commands->size)
    {
        switch ((int)commands->massive_of_code[cur_ind])
        {
            #include "commands.h"
            default:
                tag_exist = 0;
                for (int i = 0; i < commands->tag_number; i++)
                {
                    if (1000 + i == (int)commands->massive_of_code[cur_ind])
                    {
                        tag_exist++;
                        cur_ind++;
                        tag_exist = 1;
                        break;
                    }
                }
                if (tag_exist == 0)
                {
                    printf("this hui: %d\n", (int)commands->massive_of_code[cur_ind]);
                    new_assert("There is unknown tag");

                }
        }
    }
    fprintf(stdout, "Stack: ");
    PrintStack(&commands->data_stk);
#include "registers.h"
}

//---------------------------------------------------------------------

#undef DEF_CMD
#undef REGISTER
