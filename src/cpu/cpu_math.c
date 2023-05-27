/**
 *  ___________  _____   _
 * |____ | ___ \/  __ \ | |
 *     / / |_/ /| /  \/ | | __ _ _ __   __ _ _   _  __ _  __ _  ___
 *     \ \ ___ \| |     | |/ _` | '_ \ / _` | | | |/ _` |/ _` |/ _ \
 * .___/ / |_/ /| \__/\ | | (_| | | | | (_| | |_| | (_| | (_| |  __/
 * \____/\____/  \____/ |_|\__,_|_| |_|\__, |\__,_|\__,_|\__, |\___|
 *                                     __/ |             __/ |
 *                                    |___/             |___/
 * DESCRIPTION:
 * Code refers registers for the arithmetic logic unit.
 *
 * BRIEF:
 * Low-level language, tiny virtual machine, intermediate representation,
 * embeddable, easy for beginners. (Friendly Punched cards)
 *
 * AUTHOR:
 * Copyright (C) 2020 Rodrigo Dornelles.
 *
 * LICENSE:
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License,
 * or any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#define TBC_SOURCE_ENTRY
#include "3bc.h"

/**
 * @ref alu_common_simple
 */
void cpu_math(struct app_3bc_s* const self)
{
     do {
        if (self->rc == TBC_RET_OK) {
            self->cache_l2.i16[0] = self->cpu.ra;
            if (self->cpu.ry) {
                self->rc = TBC_RET_SYS_MEM_READ;
                break;
            } 
            self->cpu.ra = self->cpu.rz;
        }

        if (self->rc == TBC_RET_SYS_MEM_READ) {
            self->rc = TBC_RET_OK;
        }

        if (self->rc == TBC_RET_OK) {
            self->rc = TBC_RET_SYS_MATH;
            if (self->cpu.rm == TBC_MODE_MATH_MUL_ADD) {
                self->cache_l1.math = self->cpu.rx;
            } else {
                self->cache_l1.math = self->cpu.rm;
            }
            self->cache_l2.i16[1] = self->cpu.ra;
            break;
        }

        if (self->rc == TBC_RET_SYS_MATH) {
            self->rc = TBC_RET_GC_LV2;
            break;
        }

        self->rc = TBC_RET_OK;
        break;
    }
    while (0);
}
