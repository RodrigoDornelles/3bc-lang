#include <stdio.h>
#include <stdlib.h>
#include "header.h"

void cpu_null(PARAMS_DEFINE){}

void cpu_mode(PARAMS_DEFINE)
{
    VALIDATE_NOT_ADRESS
    tape_router_cpu_set(value);
}

void cpu_not_mode(PARAMS_DEFINE)
{
    fprintf(stderr, "[!] [3BC] [CRITICAL ERROR] EMPUTY CPU MODE");
    lang_driver_exit(EXIT_FAILURE);
}

void cpu_not_duality(PARAMS_DEFINE)
{
    fprintf(stderr, "[!] [3BC] [CRITICAL ERROR] DUALITY ADDRES WITH VALUE IN SINGLE REGISTER");
    lang_driver_exit(EXIT_FAILURE);
}

void cpu_not_exist(PARAMS_DEFINE)
{
    fprintf(stderr, "[!] [3BC] [CRITICAL ERROR] REGISTER NOT EXIST IN CPU MODE");
    lang_driver_exit(EXIT_FAILURE);
}

void cpu_not_addres(PARAMS_DEFINE)
{
    fprintf(stderr, "[!] [3BC] [CRITICAL ERROR] NOT ALOWED ADDRES");
    lang_driver_exit(EXIT_FAILURE);
}

void cpu_not_value(PARAMS_DEFINE)
{
    fprintf(stderr, "[!] [3BC] [CRITICAL ERROR] NOT ALOWED VALUE");
    lang_driver_exit(EXIT_FAILURE); 
}

void cpu_required_addres(PARAMS_DEFINE)
{
    fprintf(stderr, "[!] [3BC] [CRITICAL ERROR] ADDRES IS REQUIRED");
    lang_driver_exit(EXIT_FAILURE);
}

void cpu_required_value(PARAMS_DEFINE)
{
    fprintf(stderr, "[!] [3BC] [CRITICAL ERROR] VALUE IS REQUIRED");
    lang_driver_exit(EXIT_FAILURE); 
}

void cpu_mode_protected(PARAMS_DEFINE)
{
    fprintf(stderr, "[!] [3BC] [CRITICAL ERROR] PROTECTED CPU MODE");
    lang_driver_exit(EXIT_FAILURE);
}