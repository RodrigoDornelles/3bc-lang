#include "driver_cpu.h"
#include "bus_cpu_0000.h"

/**
 * @throw ERROR_INVALID_CPU_MODE
 * @throw ERROR_INVALID_REGISTER
 */
void driver_cpu(struct app_3bc_s* const self)
{
    do {
        if (self->cpu.rx == NILL) {
            self->hyperload = NULL;
            break;
        }
        if (self->cpu.rx == MODE) {
            if (self->cpu.rz >= tbc_layout_cpu_modes) {
                self->rc = TBC_RET_THROW_ERROR;
                self->cache_l1.error = ERROR_INVALID_CPU_MODE;
                break;
            }
            self->cpu.rm = self->cpu.rz;
            self->hyperload = NULL;
            break;
        }
        if (self->cpu.rx >= (*tbc_layout_cpu_funcs[self->cpu.rm].size)) {
            self->rc = TBC_RET_THROW_ERROR;
            self->cache_l1.error = ERROR_INVALID_REGISTER;
            break;
        }

        self->hyperload =
            (*tbc_layout_cpu_funcs[self->cpu.rm].opcodes)[self->cpu.rx - 1];
    }
    while(0);
}
