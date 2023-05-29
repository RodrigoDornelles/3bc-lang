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
    static struct app_3bc_s instance;
    instance.cin.tty_storage.io.arr.ptr = (tbc_u8_t*) prog;
    instance.stack.cfgmin.prog_size = sizeof(prog);

    while (driver_interrupt(&instance)) {
        continue;
    }

    return 0;
}
