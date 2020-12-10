#include "header.h"
#include "register.h"


void tape_output_serial_1(reg_t type, val_t val)
{
    switch(type) {
        case STRI:
            printw("%lu", (unsigned int) val);
            break;

        case STRO:
            printw("%o", (unsigned int) val);
            break;

        case STRC:
            printw("%c", (unsigned char) val);
            break;

        case STRX:
            printw("%x", (unsigned int) val);
            break;

        case STRU:
            printw("%d", (signed int) val);
            break;
    }
}

void tape_output_serial_2(reg_t type, val_t val)
{
    tape_output_serial_1(type, val);
}