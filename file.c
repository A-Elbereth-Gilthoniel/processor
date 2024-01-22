#include "processor.h"

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

void put_into_file(ELEM* massive_of_code, size_t size)
{
    char* code_file_name = "code.txt";
    FILE* fp = fopen(code_file_name, "wb");

    for (int i = 0; i < size; i++)
    {
        fprintf(fp, SPEC"\n", massive_of_code[i]);
    }
    fclose(fp);
}

//------------------------------------------------
