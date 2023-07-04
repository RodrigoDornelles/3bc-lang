#define TBC_SOURCE_ENTRY
#include "3bc.h"
#include "lang/lang_3bc_cli.h"
#include "util/util_args.h"
#include "bus/bus_sys_0000.h"

static const char ___msg_version[] = VERSION_3BC;
static const tbc_u8_t ___len_version = (tbc_i8_t) sizeof(___msg_version) * (-1);

void lang_3bc_cli_init(tbc_app_st *const self, int argc, char** argv)
{
    do {
        if (util_args_has(argc, argv, 'v') != NULL) {
            self->cache_l3.buffer.storage = (char*) ___msg_version;
            self->cache_l3.buffer.size = ___len_version;
            tbc_pkg_standard.io.write(self);
            self->rc = TBC_RET_EXIT_FORCE;
            break;
        }
    }
    while(0);
}

void lang_3bc_cli_compile(tbc_app_st *const self)
{

}
