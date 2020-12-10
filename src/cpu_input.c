#include <stdio.h>
#include <stdlib.h>
#ifndef _WIN32
#include <curses.h> 
#else
#include <conio.h> 
#endif
#include "header.h"
#include "register.h"


void cpu_input_stri(PARAMS_DEFINE)
{
    echo();
    internal_input_stri(PARAMS_USE);
}

void cpu_input_strc(PARAMS_DEFINE)
{
    echo();
    internal_input_strc(PARAMS_USE);
}

void cpu_input_stro(PARAMS_DEFINE)
{
    echo();
    internal_input_stro(PARAMS_USE);
}

void cpu_input_strx(PARAMS_DEFINE)
{
    echo();
    internal_input_strx(PARAMS_USE);
}

void cpu_input_silent_stri(PARAMS_DEFINE)
{
    noecho();
    internal_input_stri(PARAMS_USE);
}

void cpu_input_silent_strc(PARAMS_DEFINE)
{
    noecho();
    internal_input_strc(PARAMS_USE);
}

void cpu_input_silent_stro(PARAMS_DEFINE)
{
    noecho();
    internal_input_strc(PARAMS_USE);
}

void cpu_input_silent_strx(PARAMS_DEFINE)
{
    noecho();
    internal_input_strx(PARAMS_USE);
}

void cpu_input_password_stri(PARAMS_DEFINE)
{
    noecho();
    internal_input_stri(PARAMS_USE);
    cpu_string_strc(NILL, '*');
}

void cpu_input_password_strc(PARAMS_DEFINE)
{
    noecho();
    internal_input_strc(PARAMS_USE);
    cpu_string_strc(NILL, '*');

}

void cpu_input_password_stro(PARAMS_DEFINE)
{
    noecho();
    internal_input_stro(PARAMS_USE);
    cpu_string_strc(NILL, '*');
}

void cpu_input_password_strx(PARAMS_DEFINE)
{
    noecho();
    internal_input_strx(PARAMS_USE);
    cpu_string_strc(NILL, '*');
}

void internal_input_stri(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    int input_val;
    char input_key[2] = "\0";

    input_key[0] = getch();

    sscanf(input_key, "%i", &input_val);
    cpu_memory_aloc(addres, input_val);
}

void internal_input_strc(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    int input_val;
    char input_key[2] = "\0";

    input_key[0] = getch();
    cpu_memory_aloc(addres, input_key[0]);
}

void internal_input_stro(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    int input_val;
    char input_key[2] = "\0";

    input_key[0] = getch();

    sscanf(input_key, "%o", &input_val);
    cpu_memory_aloc(addres, input_val);
}

void internal_input_strx(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    int input_val;
    char input_key[2] = "\0";

    input_key[0] = getch();

    sscanf(input_key, "%x", &input_val);
    cpu_memory_aloc(addres, input_val);
}