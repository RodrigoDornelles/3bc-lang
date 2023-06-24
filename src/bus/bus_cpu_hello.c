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
 * @file bus_cpu_hello.c
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
 * @note
 * Only cpu modes 1 & 2.
 */

#define TBC_SOURCE_ENTRY
#include "bus/bus_cpu_hello.h"
#include "cpu/cpu_string.h"
#include "types/types_consts.h"

#if !defined(TBC_SCU_OPTIONAL_FIX)

static const tbc_method_ft ___bus_op_02[] = {
    cpu_string_output, cpu_string_output, cpu_string_output,
    cpu_string_output, cpu_string_output
};
static const tbc_u8_t ___bus_er_02[] = {
    TBC_DUAL_NZ, TBC_DUAL_NZ, TBC_DUAL_NZ, TBC_DUAL_NZ, TBC_DUAL_NZ
};

static const tbc_layout_cpu_st ___layout_cpu[] = {
    {
        0, NULL, NULL
    },
    {   
        sizeof(___bus_op_02), ___bus_op_02, ___bus_er_02
    },{
        sizeof(___bus_op_02), ___bus_op_02, ___bus_er_02
    }
};

const tbc_u8_t tbc_layout_cpu_modes = sizeof(___layout_cpu)/sizeof(tbc_layout_cpu_st);
const tbc_layout_cpu_st* tbc_layout_cpu_funcs = ___layout_cpu;

#endif
