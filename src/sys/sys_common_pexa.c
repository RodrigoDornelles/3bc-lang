#include "sys_common_pexa.h"

static void sys_common_pexams_expand(tbc_app_st *const self);

void sys_common_pexams_install(tbc_app_st *const self)
{
    self->pkg_func.prog.expand = &sys_common_pexams_expand;
}

static void sys_common_pexams_expand(tbc_app_st *const self)
{
    self->cache_l0.rx = TBC_OK;
    self->cin.tty_storage.io.arr.size += 3;
    self->cin.tty_storage.io.arr.ptr = realloc(self->cin.tty_storage.io.arr.ptr, self->cin.tty_storage.io.arr.size);
}