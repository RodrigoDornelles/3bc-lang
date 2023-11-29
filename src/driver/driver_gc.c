/**
 * @file src/driver/driver_gc.c
 * @short guest driver garbage colector **source code**
 * @brief Code refers the common memory cleanup of the virtual machine.
 */
#define TBC_SOURCE_ENTRY
#include "types/types_return.h"
#include "driver/driver_gc.h"
#include "bus/bus_mem_0000.h"

/**
 * @short internal garbage collector
 *
 * @brief small implementation for garbage collection routine,
 * it is used to facilitate the development of the project and
 * reduce the amount of code to release codes,
 * since all dynamic use shared memory region.
 *
 * @note the @ref TBC_RET_GC_END is internal reserved value,
 * this value convert automatic to @ref TBC_RET_GC_OK.
 * 
 * @attention the final **3bc language** programmer
 * does **not have access to the GC** feature,
 * this implementation concerns only the runtime source code.
 *
 * @startuml
 *
 * TBC_RET_GC_OK: does not interrupt
 * TBC_RET_GC_LV1: interrupt sytem
 * TBC_RET_GC_LV2: interrupt sytem
 * TBC_RET_GC_LV3: interrupt sytem
 * TBC_RET_GC_LV4: interrupt sytem
 * TBC_RET_GC_END: internal only
 *
 * [*] --> TBC_RET_GC_LV4
 * [*] --> TBC_RET_GC_LV3
 * [*] --> TBC_RET_GC_LV2
 * [*] --> TBC_RET_GC_LV1
 * TBC_RET_GC_LV4 --> TBC_RET_GC_LV3
 * TBC_RET_GC_LV3 --> TBC_RET_GC_LV2
 * TBC_RET_GC_LV2 --> TBC_RET_GC_LV1
 * TBC_RET_GC_LV1 --> TBC_RET_GC_END
 * TBC_RET_GC_END --> TBC_RET_GC_OK
 * TBC_RET_GC_OK --> [*]
 *
 * @enduml
 */
void driver_gc(struct app_3bc_s* const self)
{
    tbc_u8_t index = 0;
    tbc_u8_t* buf = NULL;

    /* cleanup **/
    switch((tbc_u8_t) self->rc)
    {
        case TBC_RET_GC_LV4:
            if (tbc_mem.free_func != NULL) {
                tbc_mem.free_func(self->cache_l3.buffer.storage);
            }
            break;

        case TBC_RET_GC_LV3:
            buf = ((tbc_u8_t*) &self->cache_l3);
            while (index < sizeof(union cache_l3_u)) {
                buf[index] ^= buf[index];
                ++index;
            }
            break;

        case TBC_RET_GC_LV2:
            buf = ((tbc_u8_t*) &self->cache_l2);
            while (index < sizeof(union cache_l2_u)) {
                buf[index] ^= buf[index];
                ++index;
            }
            break;

        case TBC_RET_GC_LV1:
            buf = ((tbc_u8_t*) &self->cache_l1);
            while (index < sizeof(union cache_l1_u)) {
                buf[index] ^= buf[index];
                ++index;
            }
            break;
    }

    /* next level */
    self->rc = (tbc_return_et) (*((tbc_u8_t*) &self->rc) - 1);

    /* verify gc done rotine */
    if (self->rc == TBC_RET_GC_END) {
        self->rc = TBC_RET_GC_OK;
    }
}