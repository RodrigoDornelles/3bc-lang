/**
 * @file src/sys/sys_windows_output.c
 * @short host driver microsoft windows output **source code**
 * @brief print text using windows api
 */
#if !defined(ARDUINO)
#define TBC_SOURCE_ENTRY
#include "sys_windows_output.h"

#include <Windows.h>

void sys_windows_output(tbc_app_st *const self)
{
#if !defined(ARDUINO)
    static LPDWORD ruindows;
    static HANDLE fileptr = GetStdHandle(STD_OUTPUT_HANDLE);

    if (self->cache.l3.fixbuf.size > 0) {
        WriteFile(
            fileptr,
            self->cache.l3.fixbuf.storage,
            self->cache.l3.fixbuf.size, 
            &ruindows,
            NULL
        );
    } else {
        WriteFile(
            fileptr,
            self->cache.l3.fixbuf.storage,
            -self->cache.l3.fixbuf.size, 
            &ruindows,
            NULL
        );
    }
#endif
}


#endif
