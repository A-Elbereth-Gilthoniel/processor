#define ACCESSING_RAM (middle_buffer[strlen(middle_buffer) - 1] == ']' &&\
                 middle_buffer[0] == '[')

#define IS_TAG_LINK (tag_is_next == 1)

#define IS_VALUE (only_numeric_symbols(middle_buffer, length - 1))

#define IS_TAG (middle_buffer[strlen(middle_buffer) - 1] == ':')

#define IS_CALL_OR_JUMP (cmp_with_number(massive_of_code[current_index], (ELEM)CALL) ||\
 ((int)massive_of_code[current_index] >= JMP && (int)massive_of_code[current_index] <= JNE))

#define IS_REG_PUSH (100 <= (int)massive_of_code[current_index] &&\
             (int)massive_of_code[current_index] <= (100 + REG_NUM) &&\
              (int)massive_of_code[current_index - 1] == PUSH)

#define IS_POP ((int)massive_of_code[current_index - 1] == POP)

#define IS_PUSH ((int)massive_of_code[current_index - 1] == PUSH)
