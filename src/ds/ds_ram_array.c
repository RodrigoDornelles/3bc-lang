#include "types/types_consts.h"
#include "ds/ds_ram_array.h"

/** @TODO: move to object app **/
static tbc_u16_t internal_ram[TBC_MAX_RAM];

void ds_ram_array_write(tbc_app_st *const self)
{
    internal_ram[self->cpu.ry - 1] = self->cpu.ra;
}

void ds_ram_array_read(tbc_app_st *const self)
{
    self->cpu.ra = internal_ram[self->cpu.ry - 1];
}
