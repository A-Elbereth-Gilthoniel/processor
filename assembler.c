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
   // printf("%d\n", *tag_number);
    int current_index = 0;
    char* new_line_pos = 0;
    int length = 0;
    int tag_is_next = 0;
   // fprintf(stdout, "%s\n", from);
    char** tag_names = (char**)calloc(number_lines, sizeof(char*));

    while (new_line_pos = strchr(from, ' '))
    {
        length = new_line_pos - from + 1;
        char* middle_buffer = (char*)calloc(length, sizeof(char));
        strncpy(middle_buffer, from, length - 1);

        if (tag_is_next == 1)
        {
            int tag_ind = check_tag_existing(tag_names, middle_buffer, *tag_number);

            if (tag_ind != -1)
                    massive_of_code[current_index] = (ELEM)(1000 + tag_ind);

            else
            {
                tag_massive[*tag_number] = (ELEM)(1000 + *tag_number);
                tag_names[*tag_number] = (char*)calloc(strlen(middle_buffer) + 1, sizeof(char));
                strncpy(tag_names[*tag_number], middle_buffer, strlen(middle_buffer));
                massive_of_code[current_index] = (ELEM)(1000 + *tag_number);
                (*tag_number)++;
            }
            tag_is_next = 0;
        }




        else if (only_numeric_symbols(middle_buffer, length - 1))
        {
            ELEM value = 0;
            sscanf(middle_buffer, SPEC, &value);
            massive_of_code[current_index] = value;
        }


        else if (middle_buffer[strlen(middle_buffer) - 1] == ':')
        {
            middle_buffer[strlen(middle_buffer) - 1] = '\0';

            int tag_ind = check_tag_existing(tag_names, middle_buffer, *tag_number);

            if (tag_ind != -1)
            {
                massive_of_code[current_index] = (ELEM)(1000 + tag_ind);
                tag_indexs[tag_ind] = current_index;
            }

            else
            {
                tag_massive[*tag_number] = (ELEM)(1000 + *tag_number);
                tag_indexs[*tag_number] = current_index;
                tag_names[*tag_number] = (char*)calloc(1000 + *tag_number + 1, sizeof(char));
                strncpy(tag_names[*tag_number], middle_buffer, (ELEM)(1000 + *tag_number));
                massive_of_code[current_index] = (ELEM)(1000 + *tag_number);
                (*tag_number)++;
            }
        }




        else
        {
            massive_of_code[current_index] = assembler_encoding(middle_buffer);

            if (100 <= (int)massive_of_code[current_index] && (int)massive_of_code[current_index] <= (100 + REG_NUM) && (int)massive_of_code[current_index - 1] == PUSH)
            {
                massive_of_code[current_index - 1] = (ELEM)RPUSH;
            }

            if (cmp_with_number(massive_of_code[current_index], (ELEM)CALL) || ((int)massive_of_code[current_index] >= JMP && (int)massive_of_code[current_index] <= JNE))
            {
                tag_is_next = 1;
            }
        }
        current_index++;
        from = from + length;
    }

    /*printf("%d Labels:\n", *tag_number);
    for (int i = 0; i < *tag_number; i++)
        printf("%s, ", tag_names[i]);*/

    for (int i = 0; i < (*tag_number); i++)
        free(tag_names[i]);
    free(tag_names);

    return current_index;
}

//-----------------------------------------------------------------------

/*void assembler_reading(COMMAND_LIST *commands)
{
    char decode_file_name[100] = "decode.txt";

    FILE *fp = fopen(decode_file_name, "rb");
    assert(fp && ("WTF?! Where's this file ''%s''!?", decode_file_name));
    size_t number_of_symbols = find_file_size(fp);

    char *text_from_file = (char*)calloc(number_of_symbols + 1, sizeof(char));
    fread(text_from_file, sizeof(char), number_of_symbols, fp);
    int number_lines = find_number_lines(text_from_file);
    text_from_file = r_replace(text_from_file, number_of_symbols);
    text_from_file = n_replace(text_from_file, number_of_symbols);

    commands->tag_massive = (ELEM*) calloc(number_lines * 2, sizeof(ELEM));
    commands->tag_indexs = (int*) calloc(number_lines * 2, sizeof(int));
    commands->massive_of_code = (ELEM*) calloc(number_of_symbols, sizeof(ELEM));

    commands->size = fill_massive_of_code(commands, number_lines, text_from_file);

    commands->massive_of_code = (ELEM*) realloc(commands->massive_of_code, (commands->size + 1) * sizeof(ELEM));
    commands->tag_massive = (ELEM*) realloc(commands->tag_massive, (commands->tag_number + 1) * sizeof(ELEM));
    commands->tag_indexs = (int*) realloc(commands->tag_indexs, (commands->tag_number + 1) * sizeof(ELEM));

    put_into_file(commands->massive_of_code, commands->size);

    FILE* output_file = fopen("code_bin.bin", "wb");

    fwrite(commands->massive_of_code, sizeof(ELEM), commands->size, output_file);

    fclose(output_file);

    fclose(fp);
}*/

//-------------------------------------------------------------------------------

/*int fill_massive_of_code(COMMAND_LIST *commands, size_t number_of_symbols, char* from)
{
    size_t true_size = 0;
    char middle_buffer[100] = {};
    int current_buf_size = 0;
    ELEM current_tag_code = (ELEM)1000;
    char** tag_names = (char**)calloc(number_of_symbols, sizeof(char*));
    size_t tag_number = 0;
    int tag_is_next = 0;
    for (int i = 0; i < number_of_symbols; i++)
    {
        if ((*(from + i) == ' ' || *(from + i) == '\n' || *(from + i) == '\r') && current_buf_size != 0 && tag_is_next == 1)
        {
            int tag_already_exist = 0;
            for (int j = 0; j < tag_number; j++)
            {
                if (string_cmptor(tag_names[j], middle_buffer) == 1)
                {
                    commands->massive_of_code[true_size] = (ELEM)(1000 + j);
                    tag_already_exist = 0;
                    break;
                }
            }
            if (tag_already_exist == 0)
            {
                commands->tag_massive[tag_number] = current_tag_code;
                printf("\n%d\n",current_tag_code);
                tag_names[tag_number] = (char*)calloc(current_buf_size + 1, sizeof(char));
                strncpy(tag_names[tag_number], middle_buffer, current_buf_size);
                commands->massive_of_code[true_size] = current_tag_code;
                current_tag_code = current_tag_code + (ELEM)1;
                tag_number++;
            }
            tag_is_next = 0;
            clear_char_massive(middle_buffer, current_buf_size);
            current_buf_size = 0;
            true_size++;
        }
        else if ((*(from + i) == ' ' || *(from + i) == '\n' || *(from + i) == '\r') && current_buf_size != 0)
        {
            if (only_numeric_symbols(middle_buffer, current_buf_size) == 1)
            {
                ELEM number = 0;
                sscanf(middle_buffer, SPEC, &number);
                commands->massive_of_code[true_size] = number;
            }
            else if (middle_buffer[current_buf_size - 1] == ':')
            {
                int tag_already_exist = 0;
                middle_buffer[current_buf_size - 1] = '\0';
                fprintf(stdout, "%s", middle_buffer);
                for (int j = 0; j < tag_number; j++)
                {
                    if (string_cmptor(tag_names[j], middle_buffer) == 1)
                    {
                        commands->massive_of_code[true_size] = (ELEM)(1000 + j);
                        commands->tag_indexs[j] = true_size;
                        tag_already_exist = 1;
                        break;
                    }
                }
                if (tag_already_exist == 0)
                {
                    commands->tag_massive[tag_number] = current_tag_code;
                    commands->tag_indexs[tag_number] = true_size;
                    printf("\n%d\n",current_tag_code);

                    tag_names[tag_number] = (char*)calloc(current_buf_size + 1, sizeof(char));
                    strncpy(tag_names[tag_number], middle_buffer, current_buf_size);

                    commands->massive_of_code[true_size] = current_tag_code;
                    current_tag_code = current_tag_code + (ELEM)1;
                    tag_number++;
                }
            }
            else
            {
                commands->massive_of_code[true_size] = assembler_encoding(middle_buffer);
                printf(SPEC" ", commands->massive_of_code[true_size]);
                if (commands->massive_of_code[true_size] > 9.5 && commands->massive_of_code[true_size] < 17.5)
                {
                    tag_is_next = 1;
                }
            }
            clear_char_massive(middle_buffer, current_buf_size);
            current_buf_size = 0;
            true_size++;
        }
        else if ((*(from + i) != ' ' && *(from + i) != '\n' && *(from + i) != '\r'))
        {
            middle_buffer[current_buf_size] = *(from + i);
            current_buf_size++;
        }
    }

    if (middle_buffer[0] != '\0')
    {
        if (only_numeric_symbols(middle_buffer, current_buf_size) == 1)
        {
            ELEM number = 0;
            sscanf(middle_buffer, SPEC, &number);
            commands->massive_of_code[true_size] = number;
        }
        else
        {
            commands->massive_of_code[true_size] = assembler_encoding(middle_buffer);
        }
        true_size++;
    }

    commands->tag_number = tag_number;

    for (int i = 0; i < tag_number; i++)
    {
        free(tag_names[i]);
    }
    free(tag_names);

    return true_size;
}*/
