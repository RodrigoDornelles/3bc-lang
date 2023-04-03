#include "cpu_common.h"
#include "bus_cpu_0000.h"

void driver_cpu(struct app_3bc_s* const self)
{
    do {
        if (self->cpu.rx == NILL) {
            self->hyperload = cpu_common_null;
            break;
        }
        if (self->cpu.rx == MODE) {
            if (self->cpu.rz >= tbc_layout_cpu_modes) {
                /** @todo: error*/
                break;
            }
            self->hyperload = cpu_common_mode;
            break;
        }
        if (self->cpu.rx >= (*tbc_layout_cpu_funcs[self->cpu.rm].size)) {
            /** @todo: error */
            break;
        }

        self->hyperload =
            (*tbc_layout_cpu_funcs[self->cpu.rm].opcodes)[self->cpu.rx - 1];
    }
    while(0);
}
