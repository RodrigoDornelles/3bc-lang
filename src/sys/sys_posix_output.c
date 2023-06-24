#include "sys_posix_output.h"

/** @todo USE OTHER DEFINE */
#if !defined(TBC_USE_ARDUINO)
#include <unistd.h>
#endif

/**
 * @todo: self->cache_l2.tty->io.fid
 */
void sys_posix_output(tbc_app_st *const self)
{
/** @todo USE OTHER DEFINE */
#if !defined(TBC_USE_ARDUINO)  
    if (self->cache_l3.fixbuf.size > 0) {
        write(
            1,
            self->cache_l3.fixbuf.storage,
            self->cache_l3.fixbuf.size
        );
    } else {
        write(
            1, 
            self->cache_l3.buffer.storage,
            -self->cache_l3.buffer.size
        );
    }
#endif
}
