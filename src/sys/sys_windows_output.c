#include <Windows.h>
#include "sys_windows_output.h"

void sys_windows_output(tbc_app_st *const self)
{
    static LPDWORD ruindows;
    static HANDLE fileptr = GetStdHandle(STD_OUTPUT_HANDLE);

    if (self->cache_l3.fixbuf.size > 0) {
        WriteFile(
            fileptr,
            self->cache_l3.fixbuf.storage,
            self->cache_l3.fixbuf.size, 
            &ruindows,
            NULL
        );
    } else {
        WriteFile(
            fileptr,
            self->cache_l3.fixbuf.storage,
            -self->cache_l3.fixbuf.size, 
            &ruindows,
            NULL
        );
    }
}
