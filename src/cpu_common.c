#include <stdio.h>
#include <stdlib.h>
#include "header.h"

void cpu_null(PARAMS){}

void cpu_mode(PARAMS)
{

}

void cpu_not_mode(PARAMS)
{
    fprintf(stderr, "[!] [3BC] [CRITICAL ERROR] EMPUTY CPU MODE");
    exit(0);
}

void cpu_not_duality(PARAMS)
{
    fprintf(stderr, "[!] [3BC] [CRITICAL ERROR] DUALITY ADDRES WITH VALUE IN SINGLE REGISTER");
    exit(0);
}

void cpu_not_exist(PARAMS)
{
    fprintf(stderr, "[!] [3BC] [CRITICAL ERROR] REGISTER NOT EXIST IN CPU MODE");
    exit(0);   
}