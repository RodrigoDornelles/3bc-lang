#include <stdio.h>
#include "header.h"


void cpu_debug_stri(PARAMS)
{
    VALIDATE_NOT_DUALITY
    fprintf(stderr, "%i", value);
}

void cpu_debug_strc(PARAMS)
{
    VALIDATE_NOT_DUALITY
    fprintf(stderr, "%c", value);
}

void cpu_debug_stro(PARAMS)
{
    VALIDATE_NOT_DUALITY
    fprintf(stderr, "%o", value);
}

void cpu_debug_strx(PARAMS)
{
    VALIDATE_NOT_DUALITY
    fprintf(stderr, "%x", value);
}