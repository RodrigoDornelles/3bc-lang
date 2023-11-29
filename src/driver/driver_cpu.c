/**
 * @file src/driver/driver_cpu.c
 * @short guest driver virtual CPU **source code**
 * @brief fetch and decode processor registers.
 */
#define TBC_SOURCE_ENTRY
#include "bus/bus_cpu_0000.h"
#include "driver/driver_cpu.h"
#include "types/types_consts.h"
#include "types/types_null.h"

/**
 * @throw ERROR_INVALID_CPU_MODE
 * @throw ERROR_INVALID_REGISTER
 * @throw ERROR_PARAM_DUALITY
 * @throw ERROR_PARAM_REQUIRE_ANY
 * @throw ERROR_PARAM_REQUIRE_VALUE
 * @throw ERROR_PARAM_REQUIRE_ADDRESS
 * @throw ERROR_PARAM_BLOCKED_VALUE
 * @throw ERROR_PARAM_BLOCKED_ADDRESS
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
            if (self->cpu.ry) {
                self->rc = TBC_RET_THROW_ERROR;
                self->cache_l1.error = ERROR_PARAM_BLOCKED_ADDRESS;
                break;
            }
            self->cpu.rm = self->cpu.rz;
            self->hyperload = NULL;
            break;
        }
        if (self->cpu.rx > tbc_layout_cpu_funcs[self->cpu.rm].size) {
            self->rc = TBC_RET_THROW_ERROR;
            self->cache_l1.error = ERROR_INVALID_REGISTER;
            break;
        }
        if ((tbc_layout_cpu_funcs[self->cpu.rm].errors[self->cpu.rx-1]&TBC_DUAL)
            && self->cpu.ry && self->cpu.rz)  {
            self->rc = TBC_RET_THROW_ERROR;
            self->cache_l1.error = ERROR_PARAM_DUALITY;
            break;
        }
        if ((tbc_layout_cpu_funcs[self->cpu.rm].errors[self->cpu.rx-1]&TBC_RYZ)
            && self->cpu.ry == 0 && self->cpu.rz == 0)  {
            self->rc = TBC_RET_THROW_ERROR;
            self->cache_l1.error = ERROR_PARAM_REQUIRE_ANY;
            break;
        }
        if ((tbc_layout_cpu_funcs[self->cpu.rm].errors[self->cpu.rx-1]&TBC_NRY)
            && self->cpu.ry != 0)  {
            self->rc = TBC_RET_THROW_ERROR;
            self->cache_l1.error = ERROR_PARAM_BLOCKED_ADDRESS;
            break;
        }
        if ((tbc_layout_cpu_funcs[self->cpu.rm].errors[self->cpu.rx-1]&TBC_NRZ)
            && self->cpu.rz != 0)  {
            self->rc = TBC_RET_THROW_ERROR;
            self->cache_l1.error = ERROR_PARAM_BLOCKED_VALUE;
            break;
        }
        if ((tbc_layout_cpu_funcs[self->cpu.rm].errors[self->cpu.rx-1]&TBC_RRY)
            && self->cpu.ry == 0)  {
            self->rc = TBC_RET_THROW_ERROR;
            self->cache_l1.error = ERROR_PARAM_REQUIRE_ADDRESS;
            break;
        }
        if ((tbc_layout_cpu_funcs[self->cpu.rm].errors[self->cpu.rx-1]&TBC_RRZ)
            && self->cpu.rz == 0)  {
            self->rc = TBC_RET_THROW_ERROR;
            self->cache_l1.error = ERROR_PARAM_REQUIRE_VALUE;
            break;
        }
        if((tbc_layout_cpu_funcs[self->cpu.rm].errors[self->cpu.rx-1]&TBC_IF)
            && self->cpu.rx > 1) {
            if (self->cpu.rx == 2 && self->cpu.ra == 0) {
                self->hyperload = NULL;
                break;
            }
            if (self->cpu.rx == 3 && self->cpu.ra != 0) {
                self->hyperload = NULL;
                break;
            }
            if (self->cpu.rx == 4 && self->cpu.ra < 0) {
                self->hyperload = NULL;
                break;
            }
            if (self->cpu.rx == 5 && self->cpu.ra > 0) {
                self->hyperload = NULL;
                break;
            }
        }

        self->hyperload =
            tbc_layout_cpu_funcs[self->cpu.rm].opcodes[self->cpu.rx - 1];
    }
    while(0);
}
