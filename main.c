#include "src/3bc.h"

int main(void)
{
    lang_driver_init();
    lang_line(MODE, NILL, MODE_MEMORY);
    lang_line(ALOC, 0x01, 'H');
    
    lang_line(NILL, NILL, 0x1);
    lang_line(MODE, NILL, MODE_STRING);
    lang_line(STRC, 0x01, NILL);
    lang_line(STRC, NILL, 'E');
    lang_line(STRC, NILL, 'L');
    lang_line(STRC, NILL, 'L');
    lang_line(STRC, NILL, 'O');
    lang_line(STRC, NILL, ' ');
    lang_line(STRC, NILL, 'W');
    lang_line(STRC, NILL, 'O');
    lang_line(STRC, NILL, 'R');
    lang_line(STRC, NILL, 'L');
    lang_line(STRC, NILL, 'D');
    lang_line(STRC, NILL, '!');
    lang_line(STRC, NILL, '\n');

    lang_line(MODE, NILL, MODE_JUMP);
    lang_line(GOTO, NILL, 0x01);

    lang_driver_run();
    lang_driver_exit(0);
    return 0;
}
