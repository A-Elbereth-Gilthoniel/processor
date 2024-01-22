#include "processor.h"

//--------------------------------------------------------------------

void clear_char_massive(char* massive, int size)
{
    for (int i = 0; i < size; i++)
        massive[i] = '\0';
}

//---------------------------------------------------------------------

int string_cmptor(char* str1, char* str2)
{
    int i = 0;
    while (str1[i] != '\0' || str2[i] != '\0')
    {
        if (str1[i] != str2[i])
            return 0;
        i++;
    }
    return 1;
}

//------------------------------------------------------------------------

void PutChar(char c)
{
    switch (c)
    {
        case '\n': fprintf(stdout, "\\n"); break;
        case '\b': fprintf(stdout, "\\b"); break;
        case '\r': fprintf(stdout, "\\r"); break;
        case '\t': fprintf(stdout, "\\t"); break;
        case '\0': fprintf(stdout, "\\0"); break;
        default: fprintf(stdout, "%c", c);
    }
}

//-----------------------------------------------------------------------
