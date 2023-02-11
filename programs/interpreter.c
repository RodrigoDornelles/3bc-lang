#include "../src/3bc.h"

/** TODO: move??? */
#include "../src/pkg/pkg_std_lang.h"
#include "../src/sys/sys_common_pfa.c"
#include "../src/sys/sys_common_pexa.c"
#include "../src/sys/sys_common_std.c"
#include "../src/pkg/pkg_std_lang.c"


static char bufferzao_gigante[100];

int main(int argc, char** argv)
{
    struct app_3bc_s* const VM = lang_3bc_init(argc, argv);
    VM->cin.tty_input.type = STREAM_TYPE_COMPUTER_STD;
    VM->cin.tty_input.io.stream = stdin;

    while (lang_3bc_update(VM)) {
        continue;
    }

    return 0;
}
