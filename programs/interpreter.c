#include "3bc.h"

int main(int argc, char** argv)
{
    int i = 0;
    static unsigned char stack[255] = {sizeof(stack)}; 
    struct app_3bc_s* const VM = lang_3bc_init(argc, argv);
    VM->cin.tty_input.type = STREAM_TYPE_COMPUTER_STD;
    VM->cin.tty_input.io.stream = stdin;
    VM->stack.raw.buffer = (unsigned char**) &stack;

    while (driver_interrupt(VM)) {
        continue;
    }

    return 0;
}
