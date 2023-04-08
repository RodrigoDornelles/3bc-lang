#include <conio.h>
#include "sys_conio_output.h"

void sys_conio_output(tbc_app_st *const self)
{
    static char *ptr;
    static tbc_u8_t index;

    index = 0;
    ptr = self->cache_l3.fixbuf.storage;

    while (index <  self->cache_l3.fixbuf.size) {
        cputc(ptr[index]);
        ++index;
    }
}
