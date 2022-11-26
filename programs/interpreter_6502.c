#define _3BC_DISABLE_INTERPRETER
#define _3BC_ENABLE_CUSTOM
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

void str_put(char* Text)
{
    cprintf ("%s", Text);
}

static struct app_3bc_s instance;

void main (void)
{
    unsigned char XSize, YSize, i;
    struct app_3bc_s *const VM = &instance;
    sys_common_pfa888_install(VM);
    VM->cin.tty_source.io.buf = (tbc_u8_t*) prog;

    lang_3bc_print(VM, tty_debug, &str_put);

    for (i = 0; i < 8; ++i) {
        VM->pkg_func.prog.load(VM);
        instruction_3bc(VM);
        VM->pkg_func.prog.next(VM);
        waitvsync();
    }
    
    while(1) {};
}
