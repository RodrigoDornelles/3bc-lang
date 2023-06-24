#include "alu_none.h"

void alu_none(struct app_3bc_s* const self)
{
    self->rc = TBC_RET_THROW_ERROR;
    self->cache_l1.error = ERROR_UNSUPPORTED;
}
