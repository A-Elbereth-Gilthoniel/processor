DEF_CMD(PUSH, 1, 1,
    DO_PUSH(handler->massive_of_code[cur_ind + 1]);
)

DEF_CMD(OUT, 2, 0,
    middle_number = DO_POP;
    DO_PUSH(middle_number);
    fprintf(stdout, ">>> "SPEC"\n", middle_number);
)



DEF_CMD(POP, 3, 1,
    number = DO_POP;
    for (int i = 0; i < REG_NUM; i++)
    {
        if ((int)handler->massive_of_code[cur_ind + 1] == (100 + i))
        {
            registers[i] = number;
            break;
        }
    }
)


DEF_CMD(IN, 4, 0,
    scanf(SPEC, &middle_number);
    DO_PUSH(middle_number);
)

DEF_CMD(HLT, 5, 0,
    cur_ind = handler->size;
)

DEF_CMD(MUL, 6, 0,
    middle_number = DO_POP;
    middle_number2 = DO_POP;
    DO_PUSH(middle_number * middle_number2);
)

DEF_CMD(ADD, 7, 0,
    middle_number = DO_POP;
    middle_number2 = DO_POP;
    DO_PUSH(middle_number + middle_number2);
)

DEF_CMD(SUB, 8, 0,
    middle_number = DO_POP;
    middle_number2 = DO_POP;
    DO_PUSH(middle_number - middle_number2);
)

DEF_CMD(DIV, 9, 0,
    middle_number = DO_POP;
    middle_number2 = DO_POP;
    DO_PUSH(middle_number / middle_number2);
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
    for (int i = 0; i < handler->tag_number; i++)
    {
        if (1000 + i == (int)handler->massive_of_code[cur_ind + 1])
        {
            DO_PUSH_STK_CALLS(cur_ind + 1);
            cur_ind = handler->tag_indexs[i] + 1;
            break;
        }
    }
)

DEF_CMD(RET, 18, -1,
    cur_ind = (int)DO_POP_STK_CALLS;
)

DEF_CMD(RPUSH, 19, 1,
    for (int i = 0; i < REG_NUM; i++)
    {
        if ((int)handler->massive_of_code[cur_ind + 1] == (100+i))
        {
            DO_PUSH(registers[i]);
            break;
        }
    }
)

DEF_CMD(RAM_NUM_POP, 20, 1,
    number = DO_POP;
    handler->ram[(int)handler->massive_of_code[cur_ind + 1]] = number;
)

DEF_CMD(RAM_REG_POP, 21, 1,
    number = DO_POP;
    for (int i = 0; i < REG_NUM; i++)
    {
        if ((int)handler->massive_of_code[cur_ind + 1] == (100 + i))
        {
            handler->ram[(int)registers[i]] = number;
            break;
        }
    }
)

DEF_CMD(RAM_NUM_PUSH, 22, 1,
    DO_PUSH(handler->ram[(int)handler->massive_of_code[cur_ind + 1]]);
)

DEF_CMD(RAM_REG_PUSH, 23, 1,
    for (int i = 0; i < REG_NUM; i++)
    {
        if ((int)handler->massive_of_code[cur_ind + 1] == (100+i))
        {
            DO_PUSH(handler->ram[(int)registers[i]]);
            break;
        }
    }
)

DEF_CMD(SPACE, 0, 0,

)

#undef DO_JUMP
#undef DO_POP
#undef DO_POP_STK_CALLS
#undef DO_PUSH
#undef DO_PUSH_STK_CALLS
