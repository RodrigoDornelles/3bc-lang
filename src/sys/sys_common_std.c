#include <unistd.h>
#include "sys_common_std.h"

void sys_common_std9945_install(tbc_app_st *const self)
{
    /**
     * default teletype's
     */
    self->cout.tty_debug.type = STREAM_TYPE_POSIX_FILEID;
    self->cout.tty_output.type = STREAM_TYPE_POSIX_FILEID;
    self->cin.tty_source.type = STREAM_TYPE_POSIX_FILEID;
    self->cin.tty_input.type = STREAM_TYPE_POSIX_FILEID;
    /**
     * @note tty 'debug' must be set before 'output'
     * when cout is a union must be overwrite.
     */
    self->cout.tty_debug.io.fid = 2;
    self->cout.tty_output.io.fid = 1;
    self->cin.tty_source.io.fid = 0;
    self->cin.tty_input.io.fid = 0;
}

void sys_common_std9945_put(tbc_app_st *const self)
{
    /** protect disabled tty */
    if (self->cache_l2.tty) {
        write(
            self->cache_l2.tty->io.fid, 
            self->cache_l3.fixbuf.storage,
            self->cache_l3.fixbuf.size
        );
    }
}
