#define ASSEMBLER_H
#ifdef ASSEMBLER_H
#include "libr.h"

size_t find_file_size(FILE* fp);
void fill_file(char* code_file_name, ELEM* massive_of_code, size_t size);
int find_number_lines(char* string);
char* r_replace(char *orig, int size);
char* n_replace(char *orig, int size);
int fill_massive_of_code(ELEM* massive_of_code, int* tag_indexs, ELEM* tag_massive, int* tag_number, size_t number_lines, char* from);
ELEM assembler_encoding(char* command);
int only_numeric_symbols(char* buffer, size_t size_buffer);
int cmp_with_number(ELEM number1, ELEM number2);
int string_cmptor(char* str1, char* str2);
char* read_file(char* file_name, size_t* symbols_num);
void fill_bin_file(char* name_bin, int* size, int* tag_num, int* tag_indexs, ELEM* code_array);

#endif // ASSEMBLER_H
