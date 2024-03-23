#include "assembler.h"

//--------------------------------------------

size_t find_file_size(FILE* fp)
{
    fseek(fp, 0, SEEK_END);
    size_t n = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    return n;
}

//---------------------------------------------

void fill_file(char* code_file_name, ELEM* massive_of_code, size_t size)
{
    FILE* fp = fopen(code_file_name, "wb");

    for (int i = 0; i < size; i++)
    {
        fprintf(fp, SPEC"\n", massive_of_code[i]);
    }
    fclose(fp);
}

//------------------------------------------------

#define DIR_MAX_LEN 50

char* read_file(char* file_name, size_t* symbols_num)
{
    char dirf[DIR_MAX_LEN] = "./tests/";
    strncat (dirf, file_name, DIR_MAX_LEN);
    FILE *fp = fopen(dirf, "rb");
    assert(fp && ("WTF?! Where's this file ''%s''!?", file_name));

    *(symbols_num) = find_file_size(fp);

    char* text_from_file = (char*) calloc(*symbols_num + 1, sizeof(char));
    fread(text_from_file, sizeof(char), *symbols_num, fp);

    fclose(fp);

    return text_from_file;
}


//------------------------------------------------------------------

void fill_bin_file(char* name_bin, int* size, int* tag_num, int* tag_indexs, ELEM* code_array)
{
    char dirf[DIR_MAX_LEN] = "./bin/";
    strncat (dirf, name_bin, DIR_MAX_LEN);
    FILE* output_file = fopen(dirf, "wb");

    fwrite(size, sizeof(ELEM), 1, output_file);
    fwrite(tag_num, sizeof(ELEM), 1, output_file);

    for (int i = 0; i < *tag_num; i++)
    {
        fwrite(&tag_indexs[i], sizeof(ELEM), 1, output_file);
    }
    fwrite(code_array, sizeof(ELEM), *size, output_file);
}

#undef DIR_MAX_LEN
