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

/** TODO: move **/
typedef struct app_3bc_s tbc_app_st;

#include "3bc_detect.h"
#include "3bc_macros.h"
#include "types/types_primitive.h"
#include "types/types_opcodes.h"
#include "types/types_fsm.h"
#include "types/types_tty.h"
#include "types/types_cache.h"
#include "types/types_return.h"
#include "types_pkg.h"
#include "types_errors.h"

/**
 *  _   __                                 _       _____
 * | | / /                                | |     |_   _|
 * | |/ /  ___ _   ___      _____  _ __ __| |___    | |_   _ _ __   ___  ___
 * |    \ / _ \ | | \ \ /\ / / _ \| '__/ _` / __|   | | | | | '_ \ / _ \/ __|
 * | |\  \  __/ |_| |\ V  V / (_) | | | (_| \__ \   | | |_| | |_) |  __/\__ \
 * \_| \_/\___|\__, | \_/\_/ \___/|_|  \__,_|___/   \_/\__, | .__/ \___||___/
 *              __/ |                                   __/ | |
 *             |___/                                   |___/|_|
 *
 * BRIEF:
 * types used to name and compare menemonics,
 * and also configure their opcode in the compiler.
 */

/** mnemonic name as number **/
union tbc_keyword_ut {
    char name[5];
    tbc_i32_t compare;
};

/** mnemonic represents opcode **/
struct tbc_keyword_opcode_st {
    union tbc_keyword_ut keyword;
    tbc_u8_t opcode;
};

/** APPLICATION TYPES **/
typedef unsigned short int line_3bc_t;
typedef unsigned char cpumode_3bc_t;
typedef unsigned char register_3bc_t;
typedef unsigned short address_3bc_t;
typedef unsigned char label_3bc_t;
typedef unsigned char memory_conf_t;
typedef signed int data_3bc_t;
typedef signed long data_aux_3bc_t;

/** TODO: remove line_3bc_t **/
typedef line_3bc_t tbc_line_t;

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


/** DS PROCEDURE LIFO **/
struct procedure_3bc_s {
    label_3bc_t label;
    struct line_node_s* remember;
    struct procedure_3bc_s* prev;
};

/** PROGRAM MEMORY **/
struct label_node_s {
    label_3bc_t label;
    cpumode_3bc_t cpumode;
    struct label_node_s* next;
    struct line_node_s* point;
};

struct line_columns_s {
    register_3bc_t reg;
    address_3bc_t adr;
    data_3bc_t dta;
};

struct line_node_s {
    line_3bc_t line;
    struct line_node_s* next;
    struct line_columns_s column;
};

struct program_3bc_s {
    line_3bc_t last_line;
    cpumode_3bc_t last_cpu;
    label_3bc_t label_target;
    struct line_node_s* curr;
    struct line_node_s* head;
    struct line_node_s* tail;
    struct label_node_s* label_table[LABEL_HASH_SIZE];
    struct procedure_3bc_s* stack;
};

/** MEMORY PRIMARY **/
struct memory_node_s {
    bool color;
    memory_conf_t conf;
    data_3bc_t data;
    address_3bc_t address;
    struct memory_node_s* left;
    struct memory_node_s* right;
};

struct memory_3bc_s {
    struct memory_node_s* root;
    struct memory_node_s* cache;
    data_3bc_t (*data_get)(app_3bc_id, address_3bc_t);
    data_3bc_t (*conf_get)(app_3bc_id, address_3bc_t);
    void (*data_set)(app_3bc_id, address_3bc_t, data_3bc_t);
    void (*conf_set)(app_3bc_id, address_3bc_t, data_3bc_t);
};

/** APLICATION **/
struct app_3bc_s {
    app_3bc_id id;
    tbc_app_fsm_et state;
    tbc_app_fsm_et previous;
    data_aux_3bc_t mem_aux;
    cpumode_3bc_t cpu_mode;
    tbc_return_et rc;
    tbc_error_et error_code;
    tbc_cache_l0_st cache_l0;
    union cache_l1_u cache_l1;
    union cache_l2_u cache_l2;
    union cache_l3_u cache_l3;
    tbc_cin_mt cin;
    tbc_cout_mt cout;
    struct program_3bc_s program;
    struct memory_3bc_s memory;
    tbc_pkg_st* pkg_func;
};

typedef void (*function_3bc_t)(
    struct app_3bc_s* const, register_3bc_t, address_3bc_t, data_3bc_t);

/** todo: remove time.h **/
#include <time.h>

/** GLOBAL TYPES **/
union global_time_u {
#if defined(TBC_P_COMPUTER)
    struct timespec ts;
#endif
    unsigned long count;
    unsigned long micros;
    unsigned long millis;
};

#endif
