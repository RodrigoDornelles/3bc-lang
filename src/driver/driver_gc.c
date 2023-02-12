#include "types_return.h"
#include "3bc_types.h"
#include <stdlib.h>
#include <string.h>

void driver_gc(struct app_3bc_s* const self)
{
    /** cleanup **/
    switch((char) self->rc)
    {
        case TBC_RET_GC_LV4:
            free(self->cache_l3.buffer.storage);
            break;

        case TBC_RET_GC_LV3:
            memset(&self->cache_l3, 0, sizeof(union cache_l3_u));
            break;

        case TBC_RET_GC_LV2:
            memset(&self->cache_l2, 0, sizeof(union cache_l2_u));
            break;

        case TBC_RET_GC_LV1:
            memset(&self->cache_l1, 0, sizeof(union cache_l1_u));
            break;
    }

    /** next level **/
    --self->rc;

    /** finished gc **/
    if (self->rc == TBC_RET_OK) {
        self->rc = TBC_RET_GC_END;
    }
}