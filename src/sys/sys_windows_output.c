#include <Windows.h>
#include "sys_windows_output.h"

void sys_windows_output(tbc_app_st *const self)
{
    static LPDWORD ruindows; 
    /** protect disabled tty */
    if (self->cache_l2.tty) {
#if !defined(TBC_NOT_FILES)
        WriteFile(GetStdHandle(STD_OUTPUT_HANDLE),
            self->cache_l3.fixbuf.storage,
            self->cache_l3.fixbuf.size, 
            &ruindows,
            NULL
        );
#endif
    }
}
