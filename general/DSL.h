#define DO_JUMP(condition)                                          \
if (#condition != "1 == 1")                                         \
{                                                                   \
middle_number = DO_POP;                      \
middle_number2 = DO_POP;                     \
DO_PUSH(middle_number2);                     \
DO_PUSH(middle_number);                      \
}                                                                   \
if (condition)                                                      \
{                                                                   \
for (int i = 0; i < handler->tag_number; i++)                      \
{                                                                   \
    if (1000 + i == (int)handler->massive_of_code[cur_ind + 1])    \
    {                                                              \
        cur_ind = handler->tag_indexs[i] + 1;                      \
        break;                                                      \
    }                                                               \
}                                                                   \
}                                                                   \
else                                                                \
{                                                                   \
    cur_ind++;                                                      \
}

#define DO_POP StackPop(&handler->data_stk)
#define DO_POP_STK_CALLS StackPop(&handler->adress_stk)
#define DO_PUSH(val) StackPush(&handler->data_stk, val)
#define DO_PUSH_STK_CALLS(val) StackPush(&handler->adress_stk, val)
