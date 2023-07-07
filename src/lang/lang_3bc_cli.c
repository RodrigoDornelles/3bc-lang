#define TBC_SOURCE_ENTRY
#include "lang/lang_3bc_cli.h"
#include "lang/lang_3bc_put.h"
#include "util/util_itos.h"
#include "util/util_args.h"

void lang_3bc_cli_init(tbc_app_st *const self, int argc, char** argv)
{
    do {
        if (util_args_has(argc, argv, 'v') != NULL) {
            lang_3bc_put(self, 'v');
            self->rc = TBC_RET_EXIT_FORCE;
            break;
        }
        if (util_args_has(argc, argv, 'i') != NULL) {
            lang_3bc_put(self, 'i');
            self->rc = TBC_RET_EXIT_FORCE;
            break;
        }
    }
    while(0);
}

void lang_3bc_cli_compile(tbc_app_st *const self)
{

}
