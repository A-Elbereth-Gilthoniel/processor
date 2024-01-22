#include "processor.h"

//-------------------------------------------------------------

void disassembler(ELEM* massive_of_code, size_t size)
{
    char* decode_file_name = "decode.txt";
    FILE* fp = fopen(decode_file_name, "wb");
    int i = 0;
    while (i != size)
    {
        switch ((int) massive_of_code[i])
        {
            case PUSH:
                fprintf(fp, "push "SPEC"\n", massive_of_code[i+1]);
                i += 2;
                break;
            case OUT:
                fprintf(fp, "out\n");
                i++;
                break;
            case POP:
                switch ((int) massive_of_code[i + 1])
                {
                    case 100:
                        fprintf(fp, "pop ax\n");
                        break;
                    case 101:
                        fprintf(fp, "pop bx\n");
                        break;
                    case 102:
                        fprintf(fp, "pop cx\n");
                        break;
                    case 103:
                        fprintf(fp, "pop dx\n");
                        break;
                }
                i += 2;
                break;
            case IN:
                fprintf(fp, "in\n");
                i++;
                break;
            case HLT:
                fprintf(fp, "hlt\n");
                i++;
                break;
            case MUL:
                fprintf(fp, "mul\n");
                i++;
                break;
            case ADD:
                fprintf(fp, "add\n");
                i++;
                break;
            case SUB:
                fprintf(fp, "sub\n");
                i++;
                break;
            case DIV:
                fprintf(fp, "div\n");
                i++;
                break;
            case JMP:
                fprintf(fp, "jmp "SPEC"\n", massive_of_code[i+1]);
                i+=2;
                break;
            case JB:
                fprintf(fp, "jb "SPEC"\n", massive_of_code[i+1]);
                i+=2;
                break;
            case JBE:
                fprintf(fp, "jbe "SPEC"\n", massive_of_code[i+1]);
                i+=2;
                break;
            case JA:
                fprintf(fp, "ja "SPEC"\n", massive_of_code[i+1]);
                i+=2;
                break;
            case JAE:
                fprintf(fp, "jae "SPEC"\n", massive_of_code[i+1]);
                i+=2;
                break;
            case JE:
                fprintf(fp, "je "SPEC"\n", massive_of_code[i+1]);
                i+=2;
                break;
            case JNE:
                fprintf(fp, "jne "SPEC"\n", massive_of_code[i+1]);
                i+=2;
                break;
            case CALL:
                fprintf(fp, "call "SPEC"\n", massive_of_code[i+1]);
                i += 2;
                break;
            case RET:
                fprintf(fp, "ret\n");
                break;
            case RPUSH:
                switch ((int) massive_of_code[i + 1])
                {
                    case 100:
                        fprintf(fp, "push ax\n");
                    case 101:
                        fprintf(fp, "push bx\n");
                    case 102:
                        fprintf(fp, "push cx\n");
                    case 103:
                        fprintf(fp, "push dx\n");
                }
                i += 2;
                break;
        }
    }
    fclose(fp);
}

//-----------------------------------------------------------
