#include <stdio.h>

#include "src/header.h"
#include "src/register.h"
#include "src/cpu_common.c"
#include "src/cpu_string.c"

int main(void)
{
    (*instructions[0][STRC])(NILL, 'H');
    (*instructions[0][STRC])(NILL, 'E');
    (*instructions[0][STRC])(NILL, 'L');
    (*instructions[0][STRC])(NILL, 'O');
    (*instructions[0][STRC])(NILL, ' ');
    (*instructions[0][STRC])(NILL, 'W');
    (*instructions[0][STRC])(NILL, 'O');
    (*instructions[0][STRC])(NILL, 'R');
    (*instructions[0][STRC])(NILL, 'D');
    (*instructions[0][STRC])(NILL, '!');
    (*instructions[0][STRC])(NILL, '\n');


    return 0;
}
