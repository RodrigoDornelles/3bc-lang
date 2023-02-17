#include "3bc.h"

int main(int argc, char** argv)
{
    struct app_3bc_s* const VM = lang_3bc_init(argc, argv);
    VM->cin.tty_input.type = STREAM_TYPE_COMPUTER_STD;
    VM->cin.tty_input.io.stream = stdin;

    while (driver_interrupt(VM)) {
        continue;
    }

    return 0;
}
