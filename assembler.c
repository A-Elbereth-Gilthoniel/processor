#include "assembler.h"

//---------------------------------------------------------------------

int main()
{
    char decode_file_name[100] = "";
    scanf("%s", decode_file_name);
    size_t symbols_num = 0;

    char *text_from_file = read_file(decode_file_name, &symbols_num);

    int number_lines = find_number_lines(text_from_file);
    text_from_file = r_replace(text_from_file, symbols_num);   // For Windows
    text_from_file = n_replace(text_from_file, symbols_num);

    int tag_number = 0;

    ELEM* tag_massive = (ELEM*) calloc(number_lines * 2, sizeof(ELEM));
    int* tag_indexs = (int*) calloc(number_lines * 2, sizeof(int));
    memset(tag_indexs, -1, number_lines * 2 * sizeof(int));
    ELEM* massive_of_code = (ELEM*) calloc(symbols_num, sizeof(ELEM));

    int size = fill_massive_of_code(massive_of_code, tag_indexs, \
                                    tag_massive, &tag_number, number_lines, \
                                    text_from_file);


    char name_file[100]     = "code.txt";
    char name_bin_file[100] = "code.bin";

    fill_file(name_file, massive_of_code, size);
    fill_bin_file(name_bin_file, &size, &tag_number, tag_indexs, massive_of_code);

    free(tag_massive);
    free(tag_indexs);
    free(massive_of_code);
}

//---------------------------------------------------------------

int fill_massive_of_code(ELEM* massive_of_code, int* tag_indexs, ELEM* tag_massive, int* tag_number, size_t number_lines, char* from)
{
#include "asm_conditions.h"
    int current_index = 0;
    char* new_line_pos = 0;
    int length = 0;
    int tag_is_next = 0;
    int is_ram = 0;
    char** tag_names = (char**)calloc(number_lines, sizeof(char*));
    char* last_command = (char*) calloc(75, sizeof(char));
    char* middle_buffer = (char*) calloc(75, sizeof(char));

    while (new_line_pos = strchr(from, ' '))
    {
        length = new_line_pos - from + 1;
        strncpy(middle_buffer, from, length - 1);
        middle_buffer[length - 1] = '\0';
        from = from + length;
        if IS_INSIGN_VALUE
            continue;

        if ACCESSING_RAM
        {
            char ram_value[50] = {};
            is_ram = 1;
            strncpy(ram_value, middle_buffer + 1, length - 3);
            strncpy(middle_buffer, ram_value, length - 3);
            middle_buffer[length - 3] = '\0';
            length = length - 2;
            if IS_POP
                massive_of_code[current_index - 1] = IS_VALUE ? (ELEM)RAM_NUM_POP : (ELEM)RAM_REG_POP;
            if IS_PUSH
                massive_of_code[current_index - 1] = IS_VALUE ? (ELEM)RAM_NUM_PUSH : (ELEM)RAM_REG_PUSH;
        }

        if IS_TAG_LINK
        {
            int tag_ind = check_tag_existing(tag_names, middle_buffer, *tag_number);

            if (tag_ind != -1)
                    massive_of_code[current_index] = (ELEM)(1000 + tag_ind);

            else
            {
                tag_names[*tag_number] = (char*)calloc(length, sizeof(char));

                make_tag(tag_massive, *tag_number, middle_buffer, tag_names);

                massive_of_code[current_index] = (ELEM)(1000 + *tag_number);

                (*tag_number)++;
            }
            tag_is_next = 0;
        }

        else if IS_VALUE
        {
            ELEM value = 0;
            sscanf(middle_buffer, SPEC, &value);
            massive_of_code[current_index] = value;
        }

        else if IS_TAG
        {
            middle_buffer[length - 2] = '\0';

            int tag_ind = check_tag_existing(tag_names, middle_buffer, *tag_number);

            if (tag_ind != -1)
            {
                massive_of_code[current_index] = (ELEM)(1000 + tag_ind);
                tag_indexs[tag_ind] = current_index;
            }

            else
            {
                tag_indexs[*tag_number] = current_index;
                tag_names[*tag_number] = (char*)calloc(1000 + *tag_number + 1, sizeof(char));

                make_tag(tag_massive, *tag_number, middle_buffer, tag_names);

                massive_of_code[current_index] = (ELEM)(1000 + *tag_number);
                (*tag_number)++;
            }
        }

        else
        {
            massive_of_code[current_index] = assembler_encoding(middle_buffer);

            if IS_REG_PUSH
                massive_of_code[current_index - 1] = (ELEM)RPUSH;

            if IS_CALL_OR_JUMP
                tag_is_next = 1;
        }
        asm_verification(last_command, middle_buffer, massive_of_code[current_index], &is_ram);
        strncpy(last_command, middle_buffer, length - 1);
        last_command[length - 1] = '\0';

        current_index++;
    }

    tag_verification(tag_names, tag_indexs, *tag_number);

    for (int i = 0; i < (*tag_number); i++)
        free(tag_names[i]);
    free(tag_names);
    free(middle_buffer);
    free(last_command);

    return current_index;
}

//-----------------------------------------------------------------------

void make_tag(ELEM* tag_massive, int tag_number, char* middle_buffer, char** tag_names)
{
    tag_massive[tag_number] = (ELEM)(1000 + tag_number);
    strncpy(tag_names[tag_number], middle_buffer, strlen(middle_buffer));
}

//-----------------------------------------------------------------------
