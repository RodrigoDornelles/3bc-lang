/**
 * @file src/sys/sys_posix_output.c
 * @short host driver posix systems output **source code**
 * @brief print text on unix plataforms: linux, bsd and macos.
 */
#define TBC_SOURCE_ENTRY
#include "sys_posix_output.h"

/** @todo USE OTHER DEFINE */
#if !defined(TBC_USE_ARDUINO) && !defined(TBC_TCC_NOSTDINC)
#include <unistd.h>
#endif

/**
 * @todo: self->cache.l2.tty->io.fid
 */
void sys_posix_output(tbc_app_st *const self)
{
/** @todo USE OTHER DEFINE */
#if !defined(TBC_USE_ARDUINO) && !defined(TBC_TCC_NOSTDINC)
    if (self->cache.l3.fixbuf.size > 0) {
        write(
            1,
            self->cache.l3.fixbuf.storage,
            self->cache.l3.fixbuf.size
        );
    } else {
        write(
            1, 
            self->cache.l3.buffer.storage,
            -self->cache.l3.buffer.size
        );
    }
#endif
}
