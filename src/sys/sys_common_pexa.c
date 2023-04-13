#include "sys_common_pexa.h"
#if !defined(TBC_NOT_MALLOC)
#include <stdlib.h>
#endif

void sys_common_pexams_install(tbc_app_st *const self)
{
    self->pkg_func->prog.expand = &sys_common_pexams_expand;
}

void sys_common_pexams_expand(tbc_app_st *const self)
{
    /** @todo raise error */
#if !defined(TBC_NOT_MALLOC)
    self->rc = TBC_RET_OK;
    self->cin.tty_storage.io.arr.size += 3;
    self->cin.tty_storage.io.arr.ptr = realloc(self->cin.tty_storage.io.arr.ptr, self->cin.tty_storage.io.arr.size);
#endif
}