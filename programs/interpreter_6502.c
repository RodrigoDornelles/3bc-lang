/*
** Fancy hello world program using cc65.
**
** Ullrich von Bassewitz (ullrich@von-bassewitz.de)
**
*/
#define _3BC_DISABLE_INTERPRETER
#define _3BC_ENABLE_CUSTOM
#include "../src/3bc.h"

void str_int()
{
    /* Set screen colors */
    textcolor (COLOR_WHITE);
    bgcolor (COLOR_BLUE);

    /* Clear the screen, put cursor in upper left corner */
    clrscr ();

    /* Reset position */
    gotoxy (0, 0);
    cprintf ("\n");
}

void str_put(char* Text)
{
    cprintf ("%s", Text);
}

void main (void)
{
    unsigned char XSize, YSize;  
    struct app_3bc_s* const VM = lang_3bc_init();

    str_int();
    waitvsync();

    lang_3bc_print(VM, tty_debug, &str_put);
    lang_3bc_line(VM, MODE, NILL, TBC_MODE_DEBUG);
    lang_3bc_line(VM, STRC, NILL, 'H');
    lang_3bc_line(VM, STRC, NILL, 'E');
    lang_3bc_line(VM, STRC, NILL, 'L');
    lang_3bc_line(VM, STRC, NILL, 'L');
    lang_3bc_line(VM, STRC, NILL, 'O');
    lang_3bc_line(VM, STRC, NILL, 0x20);
    lang_3bc_line(VM, STRC, NILL, 'W');
    lang_3bc_line(VM, STRC, NILL, 'O');
    lang_3bc_line(VM, STRC, NILL, 'R');
    lang_3bc_line(VM, STRC, NILL, 'L');
    lang_3bc_line(VM, STRC, NILL, 'D');
    lang_3bc_line(VM, STRC, NILL, '!');
    lang_3bc_line(VM, STRC, NILL, '\n');

    while (1) {
        waitvsync();
        lang_3bc_update(VM);
    }
}