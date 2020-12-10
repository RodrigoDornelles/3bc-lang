#include "src/header.h"
#include "src/register.h"
#include "src/cpu_common.c"
#include "src/cpu_debug.c"
#include "src/cpu_input.c"
#include "src/cpu_memory.c"
#include "src/cpu_string.c"
#include "src/lang_line.c"
#include "src/lang_driver.c"
#include "src/parser_interpreter.c"
#include "src/parser_transpiler.c"
#include "src/parser_compiler.c"
#include "src/tape_aux.c"
#include "src/tape_input.c"
#include "src/tape_memory.c"
#include "src/tape_program.c"
#include "src/tape_output.c"
#include "src/tape_router.c"

int main(void)
{
    lang_driver_init();
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
    lang_driver_exit(0);
    return 0;
}
