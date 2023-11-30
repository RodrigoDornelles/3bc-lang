/**
 * @file src/sys/sys_conio_output.c
 * @short host driver microsoft msdos output **source code**
 * @brief print text using msdos api
 */
#define TBC_SOURCE_ENTRY
#include "sys_conio_output.h"

/** @todo USE OTHER DEFINE */
#if !defined(TBC_USE_ARDUINO)
#include <conio.h>
#endif

void sys_conio_output(tbc_app_st *const self)
{
/** @todo USE OTHER DEFINE */
#if !defined(TBC_USE_ARDUINO)
    static char *ptr;
    static tbc_u8_t index;

    index = 0;
    ptr = self->cache_l3.fixbuf.storage;

    while (index <  self->cache_l3.fixbuf.size) {
        cputc(ptr[index]);
        ++index;
    }
#endif
}
