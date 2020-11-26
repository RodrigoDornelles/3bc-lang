#include <stdio.h>
#include "header.h"

void cpu_string_stri(mem_t addres, mem_t value)
{
    VALIDATE_NOT_DUALITY
    fprintf(stdout, "%i", value);
}

void cpu_string_strc(mem_t addres, mem_t value)
{
    VALIDATE_NOT_DUALITY
    fprintf(stdout, "%c", value);
}

void cpu_string_stro(mem_t addres, mem_t value)
{
    VALIDATE_NOT_DUALITY
    fprintf(stdout, "%o", value);
}

void cpu_string_strx(mem_t addres, mem_t value)
{
    VALIDATE_NOT_DUALITY
    fprintf(stdout, "%x", value);
}