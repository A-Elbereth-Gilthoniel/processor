#include "processor.h"

//--------------------------------------------

/*void do_pop(STACK *stk, ELEM data, ELEM* ax, ELEM* bx, ELEM* cx, ELEM* dx)
{
    ELEM number = StackPop(stk);
    switch ((int)data)
    {
        case AX:
            *ax = number;
            break;
        case BX:
            *bx = number;
            break;
        case CX:
            *cx = number;
            break;
        case DX:
            *dx = number;
            break;
        default:
            assert(NULL);
    }
}*/

//-------------------------------------------------------------

/*void do_jump(COMMAND_LIST *commands, int *cur_ind)
{
    for (int i = 0; i < commands->tag_number; i++)
    {
        if (1000 + i == (int)commands->massive_of_code[*(cur_ind) + 1])
        {
           // fprintf(stdout, "index: %d\n", commands->tag_indexs[i]);
            *(cur_ind) = commands->tag_indexs[i] + 1;
            break;
        }
    }
}*/

//-------------------------------------------------------------

#define DEF_CMD(name, code, arg_num, program)\
case code: \
    program \
    cur_ind = cur_ind + 1 + (arg_num); \
    break;

#define REGISTER(name, code) fprintf(stdout, #name" = "SPEC", ", registers[code - 100]);

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
        /*if ((int)commands->massive_of_code[cur_ind] != SPACE)
        {
        printf("Current command: %d ", (int)commands->massive_of_code[cur_ind]);
        #include "registers.h"
        }*/
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
                    new_assert("There is unknown tag");
        }
    }
    fprintf(stdout, "Stack: ");
    PrintStack(&commands->data_stk);
#include "registers.h"
}

//---------------------------------------------------------------------

#undef DEF_CMD
#undef REGISTER















/*
case PUSH:
                StackPush(&commands->data_stk, commands->massive_of_code[cur_ind + 1]);
                cur_ind += 2;
                break;
            case OUT:
                middle_number = StackPop(&commands->data_stk);
                StackPush(&commands->data_stk, middle_number);
                fprintf(stdout, ">>> "SPEC"\n", middle_number);
                cur_ind++;
                break;
            case POP:
                do_pop(&commands->data_stk, commands->massive_of_code[cur_ind + 1], &ax, &bx, &cx, &dx);
                cur_ind += 2;
                break;
            case IN:
                scanf(SPEC, &middle_number);
                StackPush(&commands->data_stk, middle_number);
                cur_ind++;
                break;
            case HLT:
                cur_ind = commands->size;
                fprintf(stdout, "privet\n");
                break;
            case MUL:
                middle_number = StackPop(&commands->data_stk);
                middle_number2 = StackPop(&commands->data_stk);
                StackPush(&commands->data_stk, middle_number * middle_number2);
                cur_ind++;
                break;
            case ADD:
                middle_number = StackPop(&commands->data_stk);
                middle_number2 = StackPop(&commands->data_stk);
                StackPush(&commands->data_stk, middle_number + middle_number2);
                cur_ind++;
                break;
            case SUB:
                middle_number = StackPop(&commands->data_stk);
                middle_number2 = StackPop(&commands->data_stk);
                StackPush(&commands->data_stk, middle_number - middle_number2);
                cur_ind++;
                break;
            case DIV:
                middle_number = StackPop(&commands->data_stk);
                middle_number2 = StackPop(&commands->data_stk);
                StackPush(&commands->data_stk, middle_number / middle_number2);
                cur_ind++;
                break;
            case JMP:
                do_jump(commands, &cur_ind);
                break;
            case JB:
                middle_number = StackPop(&commands->data_stk);
                middle_number2 = StackPop(&commands->data_stk);
                StackPush(&commands->data_stk, middle_number2);
                StackPush(&commands->data_stk, middle_number);
                if (middle_number < middle_number2 && !cmp_with_number(middle_number, middle_number2))
                    do_jump(commands, &cur_ind);
                break;
            case JBE:
                middle_number = StackPop(&commands->data_stk);
                middle_number2 = StackPop(&commands->data_stk);
                StackPush(&commands->data_stk, middle_number2);
                StackPush(&commands->data_stk, middle_number);
                if (middle_number < middle_number2 || cmp_with_number(middle_number, middle_number2))
                    do_jump(commands, &cur_ind);
                break;
            case JA:
                middle_number = StackPop(&commands->data_stk);
                middle_number2 = StackPop(&commands->data_stk);
                StackPush(&commands->data_stk, middle_number2);
                StackPush(&commands->data_stk, middle_number);
                if (middle_number > middle_number2 && !cmp_with_number(middle_number, middle_number2))
                    do_jump(commands, &cur_ind);
                break;
            case JAE:
                middle_number = StackPop(&commands->data_stk);
                middle_number2 = StackPop(&commands->data_stk);
                StackPush(&commands->data_stk, middle_number2);
                StackPush(&commands->data_stk, middle_number);
                if (middle_number > middle_number2 || cmp_with_number(middle_number, middle_number2))
                    do_jump(commands, &cur_ind);
                break;
            case JE:
                middle_number = StackPop(&commands->data_stk);
                middle_number2 = StackPop(&commands->data_stk);
                StackPush(&commands->data_stk, middle_number2);
                StackPush(&commands->data_stk, middle_number);
                if (cmp_with_number(middle_number, middle_number2))
                    do_jump(commands, &cur_ind);
                break;
            case JNE:
                middle_number = StackPop(&commands->data_stk);
                middle_number2 = StackPop(&commands->data_stk);
                StackPush(&commands->data_stk, middle_number2);
                StackPush(&commands->data_stk, middle_number);
                if (!cmp_with_number(middle_number, middle_number2))
                    do_jump(commands, &cur_ind);
                break;
            case CALL:
                for (int i = 0; i < commands->tag_number; i++)
                {
                    if (1000 + i == (int)commands->massive_of_code[cur_ind + 1])
                    {
                        StackPush(&commands->adress_stk, cur_ind + 1);
                        cur_ind = commands->tag_indexs[i] + 1;
                        break;
                    }
                }
                fprintf(stdout, "\n");
                PrintStack(&commands->adress_stk);
                break;
            case RET:
                cur_ind = (int)StackPop(&commands->adress_stk);
                fprintf(stdout, "privet\n");
                break;
            case RPUSH:
                switch ((int)commands->massive_of_code[cur_ind + 1])
                {
                    case AX:
                        StackPush(&commands->data_stk, ax);
                        break;
                    case BX:
                        StackPush(&commands->data_stk, bx);
                        break;
                    case CX:
                        StackPush(&commands->data_stk, cx);
                        break;
                    case DX:
                        StackPush(&commands->data_stk, dx);
                        break;
                }
                cur_ind += 2;
                break;

            case SPACE:
              //  fprintf(stdout, "halava\n");
                cur_ind++;
                break;*/
