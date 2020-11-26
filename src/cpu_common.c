#include <stdio.h>
#include <stdlib.h>
#include "header.h"

void cpu_null(PARAMS_DEFINE){}

void cpu_mode(PARAMS_DEFINE)
{

}

void cpu_not_mode(PARAMS_DEFINE)
{
    fprintf(stderr, "[!] [3BC] [CRITICAL ERROR] EMPUTY CPU MODE");
    exit(0);
}

void cpu_not_duality(PARAMS_DEFINE)
{
    fprintf(stderr, "[!] [3BC] [CRITICAL ERROR] DUALITY ADDRES WITH VALUE IN SINGLE REGISTER");
    exit(0);
}

void cpu_not_exist(PARAMS_DEFINE)
{
    fprintf(stderr, "[!] [3BC] [CRITICAL ERROR] REGISTER NOT EXIST IN CPU MODE");
    exit(0);   
}

void cpu_not_addres(PARAMS_DEFINE)
{
    fprintf(stderr, "[!] [3BC] [CRITICAL ERROR] NOT ALOWED ADDRES");
    exit(0);   
}

void cpu_not_value(PARAMS_DEFINE)
{
    fprintf(stderr, "[!] [3BC] [CRITICAL ERROR] NOT ALOWED VALUE");
    exit(0);   
}