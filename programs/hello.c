#include "../src/3bc.h"
#include "../src/sys/sys_common_pfa.h"
#include "../src/sys/sys_common_pfa.c"

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
    VM->cin.tty_source.io.buf = (tbc_u8_t*) prog;

    for (int i = 0; i < sizeof(prog)/3; ++i) {
        VM->pkg_func.prog.load(VM);
        instruction_3bc(VM);
        VM->pkg_func.prog.next(VM);
    }
    return 0;
}
