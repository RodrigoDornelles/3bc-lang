/**
 * @file src/sys/sys_standard_output.c
 * @short host driver standard libc output **source code**
 * @brief print text as generic c language polymorphism. 
 */
#define TBC_SOURCE_ENTRY
#include "sys_standard_output.h"

#if !defined(TBC_USE_ARDUINO)
#if defined(TBC_TCC_NOSTDINC)
#include <tcclib.h>
#else
#include <stdio.h>
#endif
#endif

/**
 * @todo: self->cache.l2.tty->io.fid
 */
void sys_standard_output(tbc_app_st *const self)
{
/** @todo USE OTHER DEFINE */
#if !defined(TBC_USE_ARDUINO)
    FILE* fileout = fdopen(1, "w");
    if (self->cache.l3.fixbuf.size > 0) {
        fwrite(
            self->cache.l3.fixbuf.storage,
            sizeof(char),
            self->cache.l3.fixbuf.size,
            fileout
        );
    } else {
        fwrite(
            self->cache.l3.buffer.storage,
            sizeof(char),
            -self->cache.l3.buffer.size,
            fileout
        );
    }
    fflush(fileout);
#endif
}
