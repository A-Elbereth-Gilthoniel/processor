#define DO_JUMP(condition)                                          \
if (#condition != "1 == 1")                                         \
{                                                                   \
middle_number = StackPop(&commands->data_stk);                      \
middle_number2 = StackPop(&commands->data_stk);                     \
StackPush(&commands->data_stk, middle_number2);                     \
StackPush(&commands->data_stk, middle_number);                      \
}                                                                   \
if (condition)                                                      \
{                                                                   \
for (int i = 0; i < commands->tag_number; i++)                      \
{                                                                   \
    if (1000 + i == (int)commands->massive_of_code[cur_ind + 1])    \
    {                                                               \
        fprintf(stdout, "index!!!\n");                              \
        cur_ind = commands->tag_indexs[i] + 1;                      \
        break;                                                      \
    }                                                               \
}                                                                   \
}                                                                   \
else                                                                \
{                                                                   \
    cur_ind++;                                                      \
}

DEF_CMD(PUSH, 1, 1,
    StackPush(&commands->data_stk, commands->massive_of_code[cur_ind + 1]);
)

DEF_CMD(OUT, 2, 0,
    middle_number = StackPop(&commands->data_stk);
    StackPush(&commands->data_stk, middle_number);
    fprintf(stdout, ">>> "SPEC"\n", middle_number);
)



DEF_CMD(POP, 3, 1,
    number = StackPop(&commands->data_stk);
    for (int i = 0; i < REG_NUM; i++)
    {
        if ((int)commands->massive_of_code[cur_ind + 1] == (100 + i))
        {
            registers[i] = number;
            break;
        }
    }
)


DEF_CMD(IN, 4, 0,
    scanf(SPEC, &middle_number);
    StackPush(&commands->data_stk, middle_number);
)

DEF_CMD(HLT, 5, 0,
    cur_ind = commands->size;
)

DEF_CMD(MUL, 6, 0,
    middle_number = StackPop(&commands->data_stk);
    middle_number2 = StackPop(&commands->data_stk);
    StackPush(&commands->data_stk, middle_number * middle_number2);
)

DEF_CMD(ADD, 7, 0,
    middle_number = StackPop(&commands->data_stk);
    middle_number2 = StackPop(&commands->data_stk);
    StackPush(&commands->data_stk, middle_number + middle_number2);
)

DEF_CMD(SUB, 8, 0,
    middle_number = StackPop(&commands->data_stk);
    middle_number2 = StackPop(&commands->data_stk);
    StackPush(&commands->data_stk, middle_number - middle_number2);
)

DEF_CMD(DIV, 9, 0,
    middle_number = StackPop(&commands->data_stk);
    middle_number2 = StackPop(&commands->data_stk);
    StackPush(&commands->data_stk, middle_number / middle_number2);
)

DEF_CMD(JMP, 10, -1,
    DO_JUMP(1 == 1)
)

DEF_CMD(JB, 11, -1,
    DO_JUMP(middle_number < middle_number2 && !cmp_with_number(middle_number, middle_number2))
)

DEF_CMD(JBE, 12, -1,
    DO_JUMP(middle_number < middle_number2 || cmp_with_number(middle_number, middle_number2))
)

DEF_CMD(JA, 13, -1,
    DO_JUMP(middle_number > middle_number2 && !cmp_with_number(middle_number, middle_number2))
)

DEF_CMD(JAE, 14, -1,
    DO_JUMP(middle_number > middle_number2 || cmp_with_number(middle_number, middle_number2))
)

DEF_CMD(JE, 15, -1,
    DO_JUMP(cmp_with_number(middle_number, middle_number2))
)

DEF_CMD(JNE, 16, -1,
    DO_JUMP(!cmp_with_number(middle_number, middle_number2))
)

DEF_CMD(CALL, 17, -1,
    for (int i = 0; i < commands->tag_number; i++)
    {
        if (1000 + i == (int)commands->massive_of_code[cur_ind + 1])
        {
            StackPush(&commands->adress_stk, cur_ind + 1);
            cur_ind = commands->tag_indexs[i] + 1;
            break;
        }
    }
)

DEF_CMD(RET, 18, -1,
    printf("suka\n");
    cur_ind = (int)StackPop(&commands->adress_stk);
)

DEF_CMD(RPUSH, 19, 1,
    for (int i = 0; i < REG_NUM; i++)
    {
        if ((int)commands->massive_of_code[cur_ind + 1] == (100+i))
        {
            StackPush(&commands->data_stk, registers[i]);
            break;
        }
    }
)

DEF_CMD(SPACE, 0, 0,

)

#undef DO_JUMP
