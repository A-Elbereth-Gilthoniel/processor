#include "processor.h"

//--------------------------------------------------------

void work_with_bin_file(COMMAND_LIST* commands)
{
    FILE* file = fopen("code.bin", "rb");
    fread(&commands->size, sizeof(ELEM), 1, file);
    fread(&commands->tag_number, sizeof(ELEM), 1, file);
    commands->tag_indexs = (int*) calloc(commands->tag_number, sizeof(int));
    commands->massive_of_code = (ELEM*) calloc(commands->size, sizeof(ELEM));

    for (int i = 0; i < commands->tag_number; i++)
    {
        fread(&commands->tag_indexs[i], sizeof(ELEM), 1, file);
        fprintf(stdout, "%d\n", commands->tag_indexs[i]);
    }

    for (int i = 0; i < commands->size; i++)
    {
        fread(&commands->massive_of_code[i], sizeof(ELEM), 1, file);
       // fprintf(stdout, "%lf\n", commands->massive_of_code[i]);
    }

    fclose(file);
}

//----------------------------------------------------------
