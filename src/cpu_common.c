#include <stdio.h>
#include <stdlib.h>
#include "header.h"

void cpu_null(mem_t addres, mem_t value){}

void cpu_mode(mem_t addres, mem_t value)
{

}

void cpu_not_mode(mem_t addres, mem_t value)
{
    fprintf(stderr, "[!] [3BC] [CRITICAL ERROR] EMPUTY CPU MODE");
    exit(0);
}

void cpu_not_duality(mem_t addres, mem_t value)
{
    fprintf(stderr, "[!] [3BC] [CRITICAL ERROR] DUALITY ADDRES WITH VALUE IN SINGLE REGISTER");
    exit(0);
}