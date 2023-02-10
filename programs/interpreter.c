#include "../src/3bc.h"

/** TODO: move??? */
#include "../src/sys/sys_common_pfa.c"
#include "../src/sys/sys_common_pexa.c"
#include "../src/sys/sys_common_std.c"

static char bufferzao_gigante[100];

int main(int argc, char** argv)
{
    struct app_3bc_s* const VM = lang_3bc_init(argc, argv);
    sys_common_std9945_install(VM);

    sys_common_pfa888_install(VM);
    sys_common_pexams_install(VM);

    VM->cin.tty_input.type = STREAM_TYPE_COMPUTER_STD;
    VM->cin.tty_input.io.stream = stdin;

    while (lang_3bc_update(VM)) {
        /*fprintf(stderr, "\n[%d:%d] %x", VM->cin.tty_storage.io.arr.size/3, VM->cin.tty_storage.io.arr.index/3, VM->state);/***/

        if (VM->cin.tty_storage.io.arr.index < VM->cin.tty_storage.io.arr.size) {
            int i = VM->cin.tty_storage.io.arr.index;
            /*fprintf(stderr, " -> %02x, %02x, %02x",
                VM->cin.tty_storage.io.arr.ptr[i],
                VM->cin.tty_storage.io.arr.ptr[i + 1],
                VM->cin.tty_storage.io.arr.ptr[i + 2]
            );/**/
        }

        if (VM->cin.tty_storage.io.arr.index/3 > 6) {
            break;
        }    
    }

    fprintf(stderr, "\npas entre nos, guerra aos senhores!!\n\n");
    return 0;
}
