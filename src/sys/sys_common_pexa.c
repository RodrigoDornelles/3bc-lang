#include "sys_common_pexa.h"
#if !defined(TBC_NOT_MALLOC)
#include <stdlib.h>
#endif
#include "types/types_null.h"

/**
 * @throw ERROR_UNSUPPORTED
 * @throw ERROR_OUT_OF_MEMORY
 */
void sys_common_pexams_expand(tbc_app_st *const self)
{
#if defined(TBC_NOT_MALLOC)
    self->rc = TBC_RET_THROW_ERROR;
    self->cache_l1.error = ERROR_UNSUPPORTED;
#else
    do {
        tbc_u16_t newsize = self->stack.cfgmin.prog->size + 3;
        tbc_u8_t* newptr = (tbc_u8_t*) realloc(self->cin.tty_storage.io.arr.ptr, newsize);

        if (newptr == NULL) {
            self->rc = TBC_RET_THROW_ERROR;
            self->cache_l1.error = ERROR_OUT_OF_MEMORY;
            break;   
        }
        
        self->cin.tty_storage.io.arr.ptr = newptr;
        self->stack.cfgmin.prog->size = newsize;
        self->rc = TBC_RET_OK;
    }
    while(0);
#endif
}
