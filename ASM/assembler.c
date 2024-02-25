#include "assembler.h"

//---------------------------------------------------------------------

int main(int argc, char *argv[])
{
    char* decode_file_name = argv[1];
    asmblr assembler;
    asm_constructor(&assembler, decode_file_name);
    int size = fill_massive_of_code(&assembler);
    char name_bin_file[100] = "code.bin";
    fill_bin_file(name_bin_file, &size, &assembler.tag_number, assembler.tag_indexs, assembler.code_array);
    asm_destr(&assembler);
}

//---------------------------------------------------------------

const int MAX_BUF_LEN = 75;
const int START_TAG_IND = 1000;

int fill_massive_of_code(asmblr* assembler)
{
#include "asm_conditions.h"
    int current_index = 0;
    char* new_line_pos = 0;
    int length = 0;
    int tag_is_next = 0;
    int is_ram = 0;
    char** tag_names = (char**)calloc(assembler->number_lines, sizeof(char*));
    char* last_command = (char*) calloc(MAX_BUF_LEN, sizeof(char));
    char* middle_buffer = (char*) calloc(MAX_BUF_LEN, sizeof(char));

    while (new_line_pos = strchr(assembler->file_text, ' '))
    {
        length = new_line_pos - assembler->file_text + 1;
        strncpy(middle_buffer, assembler->file_text, length - 1);
        middle_buffer[length - 1] = '\0';
        assembler->file_text = assembler->file_text + length;
        if (IS_INSIGN_VALUE)
            continue;

        if (ACCESSING_RAM)
        {
            is_ram = 1;
            strncpy(middle_buffer, middle_buffer + 1, length - 3);
            middle_buffer[length - 3] = '\0';
            length = length - 2;
            if (IS_POP)
                assembler->code_array[current_index - 1] = IS_VALUE ? (ELEM)RAM_NUM_POP : (ELEM)RAM_REG_POP;
            if (IS_PUSH)
                assembler->code_array[current_index - 1] = IS_VALUE ? (ELEM)RAM_NUM_PUSH : (ELEM)RAM_REG_PUSH;
        }

        if (IS_TAG_LINK)
        {
            int tag_ind = check_tag_existing(tag_names, middle_buffer, assembler->tag_number);

            if (tag_ind != -1)
                    assembler->code_array[current_index] = (ELEM)(START_TAG_IND + tag_ind);

            else
            {
                tag_names[assembler->tag_number] = (char*)calloc(length, sizeof(char));

                make_tag(assembler->tag_massive, assembler->tag_number, middle_buffer, tag_names);

                assembler->code_array[current_index] = (ELEM)(START_TAG_IND + assembler->tag_number);

                (assembler->tag_number)++;
            }
            tag_is_next = 0;
        }

        else if (IS_VALUE)
        {
            ELEM value = 0;
            sscanf(middle_buffer, SPEC, &value);
            assembler->code_array[current_index] = value;
        }

        else if (IS_TAG)
        {
            middle_buffer[length - 2] = '\0';

            int tag_ind = check_tag_existing(tag_names, middle_buffer, assembler->tag_number);

            if (tag_ind != -1)
            {
                assembler->code_array[current_index] = (ELEM)(START_TAG_IND + tag_ind);
                assembler->tag_indexs[tag_ind] = current_index;
            }

            else
            {
                assembler->tag_indexs[assembler->tag_number] = current_index;
                tag_names[assembler->tag_number] = (char*)calloc(75, sizeof(char));

                make_tag(assembler->tag_massive, assembler->tag_number, middle_buffer, tag_names);

                assembler->code_array[current_index] = (ELEM)(START_TAG_IND + assembler->tag_number);
                (assembler->tag_number)++;
            }
        }

        else
        {
            assembler->code_array[current_index] = assembler_encoding(middle_buffer);

            if (IS_REG_PUSH)
                assembler->code_array[current_index - 1] = (ELEM)RPUSH;

            if (IS_CALL_OR_JUMP)
                tag_is_next = 1;
        }
        asm_verification(last_command, middle_buffer, assembler->code_array[current_index], &is_ram);
        strncpy(last_command, middle_buffer, length - 1);
        last_command[length - 1] = '\0';

        current_index++;
    }

    tag_verification(tag_names, assembler->tag_indexs, assembler->tag_number);

    for (int i = 0; i < assembler->tag_number; i++)
        free(tag_names[i]);
    free(tag_names);
    free(middle_buffer);
    free(last_command);

    return current_index;
}

//-----------------------------------------------------------------------

void make_tag(ELEM* tag_massive, int tag_number, char* middle_buffer, char** tag_names)
{
    tag_massive[tag_number] = (ELEM)(START_TAG_IND + tag_number);
    strncpy(tag_names[tag_number], middle_buffer, strlen(middle_buffer));
}

//-----------------------------------------------------------------------

void asm_constructor(asmblr* assembler, char* decode_file_name)
{
    size_t symbols_num = 0;
    assembler->file_text = read_file(decode_file_name, &symbols_num);
    assembler->number_lines = find_number_lines(assembler->file_text);
    assembler->tag_number = 0;
    assembler->tag_massive = (ELEM*) calloc(assembler->number_lines, sizeof(ELEM));
    assembler->tag_indexs = (int*) calloc(assembler->number_lines, sizeof(int));
    memset(assembler->tag_indexs, -1, assembler->number_lines * sizeof(int));
    assembler->code_array = (ELEM*) calloc(symbols_num, sizeof(ELEM));
}

//-----------------------------------------------------------------------

void asm_destr(asmblr* assembler)
{
    free(assembler->tag_massive);
    free(assembler->tag_indexs);
    free(assembler->code_array);
}
