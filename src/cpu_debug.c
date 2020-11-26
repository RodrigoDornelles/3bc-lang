#include <stdio.h>
#include "header.h"


void cpu_debug_stri(mem_t addres, mem_t value)
{
    VALIDATE_NOT_DUALITY
    fprintf(stderr, "%i", value);
}

void cpu_debug_strc(mem_t addres, mem_t value)
{
    VALIDATE_NOT_DUALITY
    fprintf(stderr, "%c", value);
}

void cpu_debug_stro(mem_t addres, mem_t value)
{
    VALIDATE_NOT_DUALITY
    fprintf(stderr, "%o", value);
}

void cpu_debug_strx(mem_t addres, mem_t value)
{
    VALIDATE_NOT_DUALITY
    fprintf(stderr, "%x", value);
}