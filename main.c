#include "processor.h"

int main()
{
    COMMAND_LIST commands;
    assembler_reading(&commands);

    STACK data_stk = {};
    STACK adress_stk = {};
    StackConstructor(&data_stk, 50);
    StackConstructor(&adress_stk, 50);
    ELEM ax = (ELEM)0, bx = (ELEM)0, cx = (ELEM)0, dx = (ELEM)0;
    ELEM middle_number = 0, middle_number2 = 0;
    int cur_ind = 0, tag_exist = 0;
    while (cur_ind != commands.size)
    {
        switch ((int)commands.massive_of_code[cur_ind])
        {
            case PUSH:
                StackPush(&data_stk, commands.massive_of_code[cur_ind + 1]);
                cur_ind += 2;
                break;
            case OUT:
                middle_number = StackPop(&data_stk);
                StackPush(&data_stk, middle_number);
                fprintf(stdout, ">>> "SPEC"\n", middle_number);
                cur_ind++;
                break;
            case POP:
                do_pop(&data_stk, commands.massive_of_code[cur_ind + 1], &ax, &bx, &cx, &dx);
                cur_ind += 2;
                break;
            case IN:
                scanf(SPEC, &middle_number);
                StackPush(&data_stk, middle_number);
                cur_ind++;
                break;
            case HLT:
                cur_ind = commands.size;
                break;
            case MUL:
                middle_number = StackPop(&data_stk);
                middle_number2 = StackPop(&data_stk);
                StackPush(&data_stk, middle_number * middle_number2);
                cur_ind++;
                break;
            case ADD:
                middle_number = StackPop(&data_stk);
                middle_number2 = StackPop(&data_stk);
                StackPush(&data_stk, middle_number + middle_number2);
                cur_ind++;
                break;
            case SUB:
                middle_number = StackPop(&data_stk);
                middle_number2 = StackPop(&data_stk);
                StackPush(&data_stk, middle_number - middle_number2);
                cur_ind++;
                break;
            case DIV:
                middle_number = StackPop(&data_stk);
                middle_number2 = StackPop(&data_stk);
                StackPush(&data_stk, middle_number / middle_number2);
                cur_ind++;
                break;
            case JMP:
                do_jump(&commands, &cur_ind);
                break;
            case JB:
                middle_number = StackPop(&data_stk);
                middle_number2 = StackPop(&data_stk);
                StackPush(&data_stk, middle_number2);
                StackPush(&data_stk, middle_number);
                if (middle_number < middle_number2 && !cmp_with_number(middle_number, middle_number2))
                    do_jump(&commands, &cur_ind);
                break;
            case JBE:
                middle_number = StackPop(&data_stk);
                middle_number2 = StackPop(&data_stk);
                StackPush(&data_stk, middle_number2);
                StackPush(&data_stk, middle_number);
                if (middle_number < middle_number2 || cmp_with_number(middle_number, middle_number2))
                    do_jump(&commands, &cur_ind);
                break;
            case JA:
                middle_number = StackPop(&data_stk);
                middle_number2 = StackPop(&data_stk);
                StackPush(&data_stk, middle_number2);
                StackPush(&data_stk, middle_number);
                if (middle_number > middle_number2 && !cmp_with_number(middle_number, middle_number2))
                    do_jump(&commands, &cur_ind);
                break;
            case JAE:
                middle_number = StackPop(&data_stk);
                middle_number2 = StackPop(&data_stk);
                StackPush(&data_stk, middle_number2);
                StackPush(&data_stk, middle_number);
                if (middle_number > middle_number2 || cmp_with_number(middle_number, middle_number2))
                    do_jump(&commands, &cur_ind);
                break;
            case JE:
                middle_number = StackPop(&data_stk);
                middle_number2 = StackPop(&data_stk);
                StackPush(&data_stk, middle_number2);
                StackPush(&data_stk, middle_number);
                if (cmp_with_number(middle_number, middle_number2))
                    do_jump(&commands, &cur_ind);
                break;
            case JNE:
                middle_number = StackPop(&data_stk);
                middle_number2 = StackPop(&data_stk);
                StackPush(&data_stk, middle_number2);
                StackPush(&data_stk, middle_number);
                if (!cmp_with_number(middle_number, middle_number2))
                    do_jump(&commands, &cur_ind);
                break;
            case CALL:
                for (int i = 0; i < commands.tag_number; i++)
                {
                    if ((int)commands.tag_massive[i] == (int)commands.massive_of_code[cur_ind + 1])
                    {
                        cur_ind = commands.tag_indexs[i] + 1;
                        StackPush(&adress_stk, commands.tag_indexs[i] + 1);
                        break;
                    }
                }
                break;
            case RET:
                cur_ind = (int)StackPop(&adress_stk);
                break;
            case RPUSH:
                switch ((int)commands.massive_of_code[cur_ind + 1])
                {
                    case AX:
                        StackPush(&data_stk, ax);
                        break;
                    case BX:
                        StackPush(&data_stk, bx);
                        break;
                    case CX:
                        StackPush(&data_stk, cx);
                        break;
                    case DX:
                        StackPush(&data_stk, dx);
                        break;
                }
                cur_ind += 2;
                break;

            default:
                tag_exist = 0;
                for (int i = 0; i < commands.tag_number; i++)
                {
                    if ((int)commands.tag_massive[i] == (int)commands.massive_of_code[cur_ind])
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
    PrintStack(&data_stk);
    printf("a = "SPEC", b = "SPEC", c = "SPEC", d = "SPEC"\n", ax, bx);

    free(commands.massive_of_code);
    free(commands.tag_indexs);
    free(commands.tag_massive);
}
