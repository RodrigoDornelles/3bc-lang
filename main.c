#include "src/3bc.h"

int main(int argc, char** argv)
{
    app_3bc_t VM = lang_3bc_init(argc, argv);
    /**
     * put transpiled program here.
     * @example:*
    lang_3bc_line(VM, MODE, NILL, MODE_STRING);
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
     */

    while (lang_3bc_update(VM))
        ;
    return 0;
}
