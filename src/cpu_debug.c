#include <stdio.h>
#include "header.h"


void cpu_debug_stri(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    AUX_USE_ANY_PARAM
    fprintf(stderr, "%i", AUX);
}

void cpu_debug_strc(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    AUX_USE_ANY_PARAM
    fprintf(stderr, "%c", AUX);
}

void cpu_debug_stro(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    AUX_USE_ANY_PARAM
    fprintf(stderr, "%o", AUX);
}

void cpu_debug_strx(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    AUX_USE_ANY_PARAM
    fprintf(stderr, "%x", AUX);
}