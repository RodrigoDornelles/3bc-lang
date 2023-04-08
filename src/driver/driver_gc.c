/**
 * @internal
 *  ___________  _____   _
 * |____ | ___ \/  __ \ | |
 *     / / |_/ /| /  \/ | | __ _ _ __   __ _ _   _  __ _  __ _  ___
 *     \ \ ___ \| |     | |/ _` | '_ \ / _` | | | |/ _` |/ _` |/ _ \
 * .___/ / |_/ /| \__/\ | | (_| | | | | (_| | |_| | (_| | (_| |  __/
 * \____/\____/  \____/ |_|\__,_|_| |_|\__, |\__,_|\__,_|\__, |\___|
 *                                     __/ |             __/ |
 *                                    |___/             |___/
 * @endinternal
 * @file driver_gc.c
 *
 * @brief
 * Code refers the common memory cleanup of the virtual machine.
 *
 * @copyright
 * Low-level language, tiny virtual machine, intermediate representation,     \n
 * embeddable, easy for beginners. (Friendly Punched cards)                   \n
 *                                                                            \n
 * Copyright (C) 2020 Rodrigo Dornelles.                                      \n
 *                                                                            \n
 * This program is free software: you can redistribute it and/or modify       \n
 * it under the terms of the GNU General Public License as published by       \n
 * the Free Software Foundation, either version 3 of the License,             \n
 * or any later version.                                                      \n
 *                                                                            \n
 * This program is distributed in the hope that it will be useful,            \n
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             \n
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              \n
 * GNU General Public License for more details.                               \n
 *                                                                            \n
 * You should have received a copy of the GNU General Public License          \n
 * along with this program.  If not, see <https://www.gnu.org/licenses/>. 
 *
 */

#include "types_return.h"
#include "3bc_types.h"
#include <stdlib.h>
#include <string.h>

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
    /* cleanup **/
    switch((tbc_u8_t) self->rc)
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

    /* next level */
    --self->rc;

    /* verify gc done rotine */
    if (self->rc == TBC_RET_GC_END) {
        self->rc = TBC_RET_GC_OK;
    }
}