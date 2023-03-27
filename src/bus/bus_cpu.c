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
 * @file bus_cpu.c
 *
 * @brief
 * Instruction set opcodes layout in virtual machine.
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

#include "3bc.h"
#include "cpu_common.h"
#include "cpu_string.h"

extern void cpu_string_output(struct app_3bc_s* const self);


struct ___layout_cpu_s {
    tbc_u8_t* size;
    tbc_method_ft** opcodes;
};

const static struct ___layout_cpu_s layout_cpu[] = {
    {
        0, NULL,
    },
    {   
        0, NULL,
    },{
        (tbc_u8_t*const)&cpu_string_layout_size,
        (tbc_method_ft**const) &cpu_string_layout_opcodes
    }
};

void bus_cpu(struct app_3bc_s* const self)
{
    do {
        if (self->cache_l0.rx == NILL) {
            self->hyperload = cpu_common_null;
            break;
        }
        if (self->cache_l0.rx == MODE) {
            self->hyperload = cpu_common_mode;
            break;
        }

        self->hyperload = (*layout_cpu[2].opcodes)[self->cache_l0.rx - 1];
    }
    while(0);
}
