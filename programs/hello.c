#include "../src/3bc.h"
#include "../src/sys/sys_common_pfa.c"
#include "../src/sys/sys_common_std.c"

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
    struct app_3bc_s* const VM = lang_3bc_init(0, NULL);
    sys_common_pfa888_install(VM);
    sys_common_std9945_install(VM);
    VM->cin.tty_source.io.arr.ptr = (tbc_u8_t*) prog;
    VM->cin.tty_source.io.arr.size = sizeof(prog);

    while (driver_interrupt(VM)) {
        continue;
    }

    return 0;
}
