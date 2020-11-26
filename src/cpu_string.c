#include <stdio.h>
#include "header.h"

void cpu_string_stri(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    fprintf(stdout, "%i", AUX);
}

void cpu_string_strc(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    AUX_USE_ANY_PARAM
    fprintf(stdout, "%c", AUX);
}

void cpu_string_stro(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    AUX_USE_ANY_PARAM
    fprintf(stdout, "%o", AUX);
}

void cpu_string_strx(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    AUX_USE_ANY_PARAM
    fprintf(stdout, "%x", AUX);
}