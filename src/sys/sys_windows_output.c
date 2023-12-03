/**
 * @file src/sys/sys_windows_output.c
 * @short host driver microsoft windows output **source code**
 * @brief print text using windows api
 */
#define TBC_SOURCE_ENTRY
#include "sys_windows_output.h"

/** @todo USE OTHER DEFINE */
#if !defined(TBC_USE_ARDUINO)
#include <Windows.h>
#endif

void sys_windows_output(tbc_app_st *const self)
{
/** @todo USE OTHER DEFINE */
#if !defined(TBC_USE_ARDUINO)
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
