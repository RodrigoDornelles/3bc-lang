#include "3bc.h"

static const tbc_u8_t prog[] = {
    NILL, NILL, NILL,
    NILL, NILL, NILL,
    MODE, NILL, TBC_MODE_STRING,
    STRX, NILL, 0xCA,
    STRX, NILL, 0xFE,
    STRC, NILL, 0x0A,
    MODE, NILL, TBC_MODE_JUMP,
    GOTO, NILL, 0x01,
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
