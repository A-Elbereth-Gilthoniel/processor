#include "assembler.h"

//--------------------------------------------

size_t find_file_size(FILE* fp)
{
    fseek(fp, 0, SEEK_END);
    size_t n = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    assert(n > 2 && "File is empty");
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

char* read_file(char* file_name, size_t* symbols_num)
{
    FILE *fp = fopen(file_name, "rb");
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
    FILE* output_file = fopen(name_bin, "wb");

    fwrite(size, sizeof(ELEM), 1, output_file);
    fwrite(tag_num, sizeof(ELEM), 1, output_file);

    for (int i = 0; i < *tag_num; i++)
    {
        fwrite(&tag_indexs[i], sizeof(ELEM), 1, output_file);
        fprintf(stdout, "%d\n", tag_indexs[i]);
    }
    fprintf(stdout, "%lf\n", code_array[0]);
    fwrite(code_array, sizeof(ELEM), *size, output_file);
}
