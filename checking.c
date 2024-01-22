#include "processor.h"

//----------------------------------------------------------------------------

int only_numeric_symbols(char* buffer, size_t size_buffer)  // Checking that only a number is entered
{
    int number_of_points = 0;
    for (int i = 0; i < size_buffer; i++)
    {
        if (buffer[i] == '.' && i != 0 && number_of_points == 0 && i != size_buffer - 1)
            number_of_points++;
        if ((!isdigit(buffer[i])) && ((buffer[i] != '-' || size_buffer == 1)|| i != 0))
            return 0;
    }
    return 1;
}

//------------------------------------------------------------------------------

int cmp_with_number(ELEM number1, ELEM number2)
{
    const double eps = 1e-5;

    return number2 - eps <= number1 && number1 <= number2 + eps;
}

//------------------------------------------------------------------------------
