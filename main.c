#include "src/3bc.h"

int main(void)
{
    lang_driver_init();

    /** 
     * put transpiled program here.
     * @example:
    lang_line(MODE, NILL, MODE_STRING);
    lang_line(STRC, NILL, 'H');
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
     */

    lang_driver_run();
    lang_driver_exit(0);
    return 0;
}
