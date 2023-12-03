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
 * Header refers to type definitions.
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

#ifndef H_TYPES_TBC
#define H_TYPES_TBC

/** @todo move **/
typedef struct app_3bc_s tbc_app_st;

#include "types/types_primitive.h"
#include "types/types_opcodes.h"
#include "types/types_fsm.h"
#include "types/types_tty.h"
#include "types/types_cpu.h"
#include "types/types_cache.h"
#include "types/types_return.h"
#include "types/types_pkg.h"
#include "types/types_errors.h"
#include "types/types_stack.h"

/** @todo remove all*/
typedef unsigned short int line_3bc_t;
typedef unsigned short int tbc_line_t;
typedef unsigned char cpumode_3bc_t;
typedef unsigned char register_3bc_t;
typedef unsigned short address_3bc_t;
typedef unsigned char label_3bc_t;
typedef unsigned char memory_conf_t;
typedef signed int data_3bc_t;
typedef signed long data_aux_3bc_t;

/** application 3bc id (depends of cpu size)**/
#if defined(TBC_ARCH_BITS_64)
#define TBC_ID_64_BITS
typedef tbc_u64_t app_3bc_id;
#define TBC_ID_32_BITS
#elif defined(TBC_ARCH_BITS_32) && !defined(TBC_OPT_COMPACT)
typedef tbc_u32_t app_3bc_id;
#elif defined(TBC_ARCH_BITS_32) || defined(TBC_ARCH_BITS_16)
#define TBC_ID_16_BITS
typedef tbc_u16_t app_3bc_id;
#elif defined(TBC_ARCH_BITS_8)
#define TBC_ID_8_BITS
typedef tbc_u8_t app_3bc_id;
#else
#define TBC_ID_16_BITS
typedef tbc_u16_t app_3bc_id;
#endif

typedef void (*tbc_method_ft)(struct app_3bc_s* const);

/** APLICATION **/
struct app_3bc_s {
    app_3bc_id id;
    tbc_app_fsm_et state;
    tbc_return_et rc;
    tbc_cpu_st cpu;
    union cache_l1_u cache_l1;
    union cache_l2_u cache_l2;
    union cache_l3_u cache_l3;
    tbc_cin_mt cin;
    tbc_cout_mt cout;
    union ___tbc_stack_root_u stack;
    tbc_pkg_st* pkg_func;
    tbc_method_ft hyperload;
};

/** @todo remove time.h **/
#if !defined(TBC_TCC_NOSTDINC)
#include <time.h>
#endif

/** GLOBAL TYPES **/
union global_time_u {
#if defined(TBC_P_COMPUTER) || !defined(TBC_TCC_NOSTDINC)
    struct timespec ts;
#endif
    unsigned long count;
    unsigned long micros;
    unsigned long millis;
};

#endif
