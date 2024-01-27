#include "processor.h"

//-----------------------------------------------------------

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
