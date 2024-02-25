#include "processor.h"

//--------------------------------------------------------

void work_with_bin_file(cpu* handler)
{
    FILE* file = fopen("./bin/code.bin", "rb");
    fread(&handler->size, sizeof(ELEM), 1, file);
    fread(&handler->tag_number, sizeof(ELEM), 1, file);
    handler->tag_indexs = (int*) calloc(handler->tag_number, sizeof(int));
    handler->massive_of_code = (ELEM*) calloc(handler->size, sizeof(ELEM));

    fread(handler->tag_indexs, sizeof(ELEM), handler->tag_number, file);
    fread(handler->massive_of_code, sizeof(ELEM), handler->size, file);

    fclose(file);
}

//----------------------------------------------------------
