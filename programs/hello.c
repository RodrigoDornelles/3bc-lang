#define _3BC_DISABLE_INTERPRETER
#include "3bc.h"

static const tbc_u8_t prog[] = {
    MODE, NILL, TBC_MODE_STRING,
    STRC, NILL, 'H',
    STRC, NILL, 'E',
    STRC, NILL, 'L',
    STRC, NILL, 'L',
    STRC, NILL, 'O',
    STRC, NILL, '!',
    STRC, NILL, '\n'
};

int main()
{
    #if defined(TBC_CONSOLE_NES)
    static struct app_3bc_s instance;
    static struct app_3bc_s* const VM = &instance;
    #else
    struct app_3bc_s* const VM = lang_3bc_init(0, NULL);
    #endif
    VM->cin.tty_storage.io.arr.ptr = (tbc_u8_t*) prog;
    VM->cin.tty_storage.io.arr.size = sizeof(prog);

    while (driver_interrupt(VM)) {
        continue;
    }

    return 0;
}
