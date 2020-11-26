#include <stdio.h>
#include "header.h"

void cpu_string_stri(PARAMS)
{
    VALIDATE_NOT_DUALITY
    fprintf(stdout, "%i", value);
}

void cpu_string_strc(PARAMS)
{
    VALIDATE_NOT_DUALITY
    fprintf(stdout, "%c", value);
}

void cpu_string_stro(PARAMS)
{
    VALIDATE_NOT_DUALITY
    fprintf(stdout, "%o", value);
}

void cpu_string_strx(PARAMS)
{
    VALIDATE_NOT_DUALITY
    fprintf(stdout, "%x", value);
}