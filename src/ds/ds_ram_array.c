#include "ds_ram_array.h"

/** @TODO: move to object app **/
static tbc_u16_t internal_ram[512];

void ds_ram_array_write(tbc_app_st *const self)
{
    internal_ram[self->cache_l0.ry] = self->cache_l0.ra;
}

void ds_ram_array_read(tbc_app_st *const self)
{
    self->cache_l0.ra = internal_ram[self->cache_l0.ry];
}
