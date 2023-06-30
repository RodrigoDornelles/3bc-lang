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
 * @file bus_cpu_lang.c
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

#define TBC_SOURCE_ENTRY
#include "bus/bus_cpu_lang.h"
#include "cpu/cpu_jump.h"
#include "cpu/cpu_math.h"
#include "cpu/cpu_memory.h"
#include "cpu/cpu_string.h"
#include "types/types_consts.h"

#if !defined(TBC_SCU_OPTIONAL_FIX)

/** @par 1-9 **/
static const tbc_method_ft ___bus_op_02[] = {
    cpu_string_output, cpu_string_output, cpu_string_output,
    cpu_string_output, cpu_string_output
};
static const tbc_u8_t ___bus_er_02[] = {
    TBC_DUAL, TBC_DUAL, TBC_DUAL, TBC_DUAL, TBC_DUAL
};
static const tbc_method_ft ___bus_op_06[] = {
    cpu_memory_free, cpu_memory_aloc
};
static const tbc_u8_t ___bus_er_06[] = {
    (TBC_RRY|TBC_NRZ), TBC_RRY
};
static const tbc_method_ft ___bus_op_07[] = {
    cpu_memory_ptr_free, cpu_memory_ptr_aloc, cpu_memory_ptr_pull,
    cpu_memory_ptr_spin, cpu_memory_ptr_push
};
static const tbc_u8_t ___bus_er_07[] = {
    TBC_NYZ, TBC_NRY, (TBC_RRY|TBC_NRZ),
    (TBC_RRY|TBC_NRZ), (TBC_RRY|TBC_NRZ)
};
static const tbc_method_ft ___bus_op_08[] = {
    cpu_memory_aux_free, cpu_memory_aux_aloc, cpu_memory_aux_pull,
    cpu_memory_aux_spin, cpu_memory_aux_push
};
static const tbc_u8_t ___bus_er_08[] = {
    TBC_NYZ, TBC_NRY, (TBC_RRY|TBC_NRZ),
    (TBC_RRY|TBC_NRZ), (TBC_RRY|TBC_NRZ)
};
static const tbc_method_ft ___bus_op_09[] = {
    cpu_jump_goto, cpu_jump_goto, cpu_jump_goto, cpu_jump_goto,
    cpu_jump_goto
};
static const tbc_u8_t ___bus_er_09[] = {
    (TBC_IF|TBC_NRY), (TBC_IF|TBC_NRY), (TBC_IF|TBC_NRY),
    (TBC_IF|TBC_NRY), (TBC_IF|TBC_NRY)
};

/** @par 11-39 **/
static const tbc_method_ft ___bus_op_math[] = {
    cpu_math
};

static const tbc_u8_t ___bus_er_math[] = {
    TBC_DUAL
};
static const tbc_method_ft ___bus_op_math_19[] = {
    cpu_math, cpu_math, cpu_math, cpu_math,
};
static const tbc_u8_t ___bus_er_math_19[] = {
    TBC_DUAL, TBC_DUAL, TBC_DUAL, TBC_DUAL,
};
static const tbc_u8_t ___bus_er_math_nryz[] = {
    (TBC_NRY|TBC_NRZ)
};

static const tbc_layout_cpu_st ___layout_cpu[] = {
    {
        0, NULL, NULL
    },
    {   
        0, NULL, NULL
    },
    {
        sizeof(___bus_er_02), ___bus_op_02, ___bus_er_02
    },
    {
        0, NULL, NULL
    },
    {
        0, NULL, NULL
    },
    {
        0, NULL, NULL
    },
    {
        sizeof(___bus_er_06), ___bus_op_06, ___bus_er_06
    },
    {
        sizeof(___bus_er_07), ___bus_op_07, ___bus_er_07
    },
    {
        sizeof(___bus_er_08), ___bus_op_08, ___bus_er_08
    },
    {
        sizeof(___bus_er_09), ___bus_op_09, ___bus_er_09
    },
    {
        0, NULL, NULL
    },
    {
        sizeof(___bus_er_math), ___bus_op_math, ___bus_er_math
    },
    {
        sizeof(___bus_er_math), ___bus_op_math, ___bus_er_math
    },
    {
        sizeof(___bus_er_math), ___bus_op_math, ___bus_er_math
    },
    {
        sizeof(___bus_er_math), ___bus_op_math, ___bus_er_math
    },
    {
        sizeof(___bus_er_math), ___bus_op_math, ___bus_er_math
    },
    {
        sizeof(___bus_er_math), ___bus_op_math, ___bus_er_math
    },
    {
        sizeof(___bus_er_math), ___bus_op_math, ___bus_er_math
    },
    {
        sizeof(___bus_er_math), ___bus_op_math, ___bus_er_math
    },
    {
        sizeof(___bus_er_math_19), ___bus_op_math_19, ___bus_er_math_19
    },
    {
        0, NULL, NULL
    },
    {
        sizeof(___bus_er_math_nryz), ___bus_op_math, ___bus_er_math_nryz
    },
    {
        sizeof(___bus_er_math), ___bus_op_math, ___bus_er_math
    },
    {
        sizeof(___bus_er_math), ___bus_op_math, ___bus_er_math
    },
    {
        sizeof(___bus_er_math), ___bus_op_math, ___bus_er_math
    },
    {
        sizeof(___bus_er_math), ___bus_op_math, ___bus_er_math
    },
    {
        sizeof(___bus_er_math), ___bus_op_math, ___bus_er_math
    },
    {
        sizeof(___bus_er_math), ___bus_op_math, ___bus_er_math
    },
    {
        sizeof(___bus_er_math), ___bus_op_math, ___bus_er_math
    },
    {
        sizeof(___bus_er_math), ___bus_op_math, ___bus_er_math
    },
    {
        0, NULL, NULL
    },
    {
        sizeof(___bus_er_math), ___bus_op_math, ___bus_er_math_nryz
    },
    {
        sizeof(___bus_er_math), ___bus_op_math, ___bus_er_math
    },
    {
        sizeof(___bus_er_math), ___bus_op_math, ___bus_er_math
    },
    {
        sizeof(___bus_er_math), ___bus_op_math, ___bus_er_math
    },
    {
        sizeof(___bus_er_math), ___bus_op_math, ___bus_er_math
    },
    {
        sizeof(___bus_er_math), ___bus_op_math, ___bus_er_math
    },
    {
        sizeof(___bus_er_math), ___bus_op_math, ___bus_er_math
    },
    {
        sizeof(___bus_er_math), ___bus_op_math, ___bus_er_math_nryz
    },
    {
        sizeof(___bus_er_math), ___bus_op_math, ___bus_er_math
    },
};

const tbc_u8_t tbc_layout_cpu_modes = sizeof(___layout_cpu)/sizeof(tbc_layout_cpu_st);
const tbc_layout_cpu_st* tbc_layout_cpu_funcs = ___layout_cpu;

#endif
