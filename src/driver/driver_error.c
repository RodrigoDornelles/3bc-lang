#include "i18n_0000.h"
#include "driver_error.h"


/**
 * @startuml
 * (*) --> "IO Write"
 * --> "Garbage Collector"
 * --> (*)
 * @enduml
 */
void driver_error(struct app_3bc_s* const self)
{
    do {
        if (self->cache_l1.error >= tbc_i18n_error_len) {
            self->cache_l1.error = 0;
        }

        if (self->rc == TBC_RET_ERROR) {
            self->rc = TBC_RET_SYS_IO_WRITE;
            self->cache_l2.tty = &(self->cout.tty_output);
            self->cache_l3.buffer.size =
                -tbc_i18n_error_arr[self->cache_l1.error].len;
            self->cache_l3.buffer.storage =
                tbc_i18n_error_arr[self->cache_l1.error].ptr;
            break;
        }

        if (self->rc == TBC_RET_SYS_IO_WRITE) {
            self->rc = TBC_RET_GC_LV3;
            break;
        }

        self->rc = TBC_RET_OK;
    }
    while(0);
}
