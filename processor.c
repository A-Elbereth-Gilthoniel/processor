#include "processor.h"

int main()
{
    COMMAND_LIST commands;
    //FILE* file = fopen("code.bin", "rb");
   /* fread(&commands.size, sizeof(ELEM), 1, file);
    fread(&commands.tag_number, sizeof(ELEM), 1, file);
    commands.tag_indexs = (int*) calloc(commands.tag_number, sizeof(int));
    commands.massive_of_code = (ELEM*) calloc(commands.size, sizeof(ELEM));*/
    work_with_bin_file(&commands);
   /* fprintf(stdout, "%d %d\n", commands.tag_number, commands.size);

    for (int i = 0; i < commands.tag_number; i++)
    {
        fread(&commands.tag_indexs[i], sizeof(ELEM), 1, file);
        fprintf(stdout, "%d\n", commands.tag_indexs[i]);
    }
   // fread(&commands.tag_indexs[0], sizeof(int), 1, file);
    fprintf(stdout, "\n");
    for (int i = 0; i < commands.size; i++)
    {
        fread(&commands.massive_of_code[i], sizeof(ELEM), 1, file);
        fprintf(stdout, "%lf\n", commands.massive_of_code[i]);
    }

    fclose(file);*/

   /* STACK data_stk = {};
    STACK adress_stk = {};*/
    StackConstructor(&commands.data_stk, 50);
    StackConstructor(&commands.adress_stk, 50);

    do_commands(&commands);
   /* ELEM ax = (ELEM)0, bx = (ELEM)0, cx = (ELEM)0, dx = (ELEM)0;
    ELEM middle_number = 0, middle_number2 = 0;
    int cur_ind = 0, tag_exist = 0;
    while (cur_ind < commands.size)
    {
        switch ((int)commands.massive_of_code[cur_ind])
        {
            case PUSH:
                StackPush(&commands.data_stk, commands.massive_of_code[cur_ind + 1]);
                cur_ind += 2;
                break;
            case OUT:
                middle_number = StackPop(&commands.data_stk);
                StackPush(&commands.data_stk, middle_number);
                fprintf(stdout, ">>> "SPEC"\n", middle_number);
                cur_ind++;
                break;
            case POP:
                do_pop(&commands.data_stk, commands.massive_of_code[cur_ind + 1], &ax, &bx, &cx, &dx);
                cur_ind += 2;
                break;
            case IN:
                scanf(SPEC, &middle_number);
                StackPush(&commands.data_stk, middle_number);
                cur_ind++;
                break;
            case HLT:
                cur_ind = commands.size;
                fprintf(stdout, "privet\n");
                break;
            case MUL:
                middle_number = StackPop(&commands.data_stk);
                middle_number2 = StackPop(&commands.data_stk);
                StackPush(&commands.data_stk, middle_number * middle_number2);
                cur_ind++;
                break;
            case ADD:
                middle_number = StackPop(&commands.data_stk);
                middle_number2 = StackPop(&commands.data_stk);
                StackPush(&commands.data_stk, middle_number + middle_number2);
                cur_ind++;
                break;
            case SUB:
                middle_number = StackPop(&commands.data_stk);
                middle_number2 = StackPop(&commands.data_stk);
                StackPush(&commands.data_stk, middle_number - middle_number2);
                cur_ind++;
                break;
            case DIV:
                middle_number = StackPop(&commands.data_stk);
                middle_number2 = StackPop(&commands.data_stk);
                StackPush(&commands.data_stk, middle_number / middle_number2);
                cur_ind++;
                break;
            case JMP:
                do_jump(&commands, &cur_ind);
                break;
            case JB:
                middle_number = StackPop(&commands.data_stk);
                middle_number2 = StackPop(&commands.data_stk);
                StackPush(&commands.data_stk, middle_number2);
                StackPush(&commands.data_stk, middle_number);
                if (middle_number < middle_number2 && !cmp_with_number(middle_number, middle_number2))
                    do_jump(&commands, &cur_ind);
                break;
            case JBE:
                middle_number = StackPop(&commands.data_stk);
                middle_number2 = StackPop(&commands.data_stk);
                StackPush(&commands.data_stk, middle_number2);
                StackPush(&commands.data_stk, middle_number);
                if (middle_number < middle_number2 || cmp_with_number(middle_number, middle_number2))
                    do_jump(&commands, &cur_ind);
                break;
            case JA:
                middle_number = StackPop(&commands.data_stk);
                middle_number2 = StackPop(&commands.data_stk);
                StackPush(&commands.data_stk, middle_number2);
                StackPush(&commands.data_stk, middle_number);
                if (middle_number > middle_number2 && !cmp_with_number(middle_number, middle_number2))
                    do_jump(&commands, &cur_ind);
                break;
            case JAE:
                middle_number = StackPop(&commands.data_stk);
                middle_number2 = StackPop(&commands.data_stk);
                StackPush(&commands.data_stk, middle_number2);
                StackPush(&commands.data_stk, middle_number);
                if (middle_number > middle_number2 || cmp_with_number(middle_number, middle_number2))
                    do_jump(&commands, &cur_ind);
                break;
            case JE:
                middle_number = StackPop(&commands.data_stk);
                middle_number2 = StackPop(&commands.data_stk);
                StackPush(&commands.data_stk, middle_number2);
                StackPush(&commands.data_stk, middle_number);
                if (cmp_with_number(middle_number, middle_number2))
                    do_jump(&commands, &cur_ind);
                break;
            case JNE:
                middle_number = StackPop(&commands.data_stk);
                middle_number2 = StackPop(&commands.data_stk);
                StackPush(&commands.data_stk, middle_number2);
                StackPush(&commands.data_stk, middle_number);
                if (!cmp_with_number(middle_number, middle_number2))
                    do_jump(&commands, &cur_ind);
                break;
            case CALL:
                for (int i = 0; i < commands.tag_number; i++)
                {
                    if (1000 + i == (int)commands.massive_of_code[cur_ind + 1])
                    {
                        StackPush(&commands.adress_stk, cur_ind + 1);
                        cur_ind = commands.tag_indexs[i] + 1;
                        break;
                    }
                }
                fprintf(stdout, "\n");
                PrintStack(&commands.adress_stk);
                break;
            case RET:
                cur_ind = (int)StackPop(&commands.adress_stk);
                fprintf(stdout, "privet\n");
                break;
            case RPUSH:
                switch ((int)commands.massive_of_code[cur_ind + 1])
                {
                    case AX:
                        StackPush(&commands.data_stk, ax);
                        break;
                    case BX:
                        StackPush(&commands.data_stk, bx);
                        break;
                    case CX:
                        StackPush(&commands.data_stk, cx);
                        break;
                    case DX:
                        StackPush(&commands.data_stk, dx);
                        break;
                }
                cur_ind += 2;
                break;

            case SPACE:
              //  fprintf(stdout, "halava\n");
                cur_ind++;
                break;

            default:
                tag_exist = 0;
                for (int i = 0; i < commands.tag_number; i++)
                {
                    if (1000 + i == (int)commands.massive_of_code[cur_ind])
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
    PrintStack(&commands.data_stk);
    printf("a = "SPEC", b = "SPEC", c = "SPEC", d = "SPEC"\n", ax, bx);*/

    free(commands.massive_of_code);
    free(commands.tag_indexs);
}
