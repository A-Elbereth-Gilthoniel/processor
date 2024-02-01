#include "assembler.h"

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


int find_number_lines(char* string)
{
    int number_lines = 0;
    for (int i = 0; i < strlen(string); i++)
    {
        if (string[i] == '\n')
            number_lines++;
    }
    if (string[strlen(string) - 1] != '\n')
        number_lines++;

    return number_lines;
}

//-----------------------------------------------------------

char* r_replace(char *orig, int size)
{
    char* result;
    char* new_str = result = (char*) calloc(size + 1, sizeof(char));
    char* insert_point;
    int n = 0;

    while (insert_point = strstr(orig, "\r"))
    {
        n = insert_point - orig;
        new_str = strncpy(new_str, orig, n) + n;
        orig = orig + n + 1;
    }

    strcpy(new_str, orig);
    return result;
}

//-----------------------------------------------------------

char* n_replace(char *orig, int size)
{
    char* result;
    char* new_str = result = (char*) calloc(size + 1, sizeof(char));
    char* insert_point;
    int n = 0;

    while (insert_point = strstr(orig, "\n"))
    {
        n = insert_point - orig;
        new_str = strncpy(new_str, orig, n) + n;
        new_str = strcpy(new_str, " ") + 1;
        orig = orig + n + 1;
    }

    strcpy(new_str, orig);
    return result;
}

//-------------------------------------------------------------------
