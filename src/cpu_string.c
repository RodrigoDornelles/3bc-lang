#include <stdio.h>
#include <stdlib.h>
#ifndef _WIN32
#include <curses.h> 
#else
#include <conio.h> 
#endif
#include "header.h"

void cpu_string_stri(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    AUX_USE_ANY_PARAM
    printw("%i", AUX);
}

void cpu_string_strc(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    AUX_USE_ANY_PARAM
    printw("%c", AUX);
}

void cpu_string_stro(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    AUX_USE_ANY_PARAM
    printw("%o", AUX);
}

void cpu_string_strx(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    AUX_USE_ANY_PARAM
    printw("%x", AUX);
}