#include <unistd.h>
#include "sys_posix_output.h"

void sys_posix_output(tbc_app_st *const self)
{
    /** protect disabled tty */
    if (self->cache_l2.tty) {
#if !defined(TBC_NOT_FILES)
        write(
            1,//self->cache_l2.tty->io.fid, 
            self->cache_l3.fixbuf.storage,
            self->cache_l3.fixbuf.size
        );
#endif
    }
}
