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

#ifndef H_DETECT_TBC
#warning "[3BC] it is recommended to \
include '3bc_detect.h' \
before '3bc_types.h'"
#endif

/**
 * ______     _           _ _   _             _____
 * | ___ \   (_)         (_) | (_)           |_   _|
 * | |_/ / __ _ _ __ ___  _| |_ ___   _____    | |_   _ _ __   ___  ___
 * |  __/ '__| | '_ ` _ \| | __| \ \ / / _ \   | | | | | '_ \ / _ \/ __|
 * | |  | |  | | | | | | | | |_| |\ V /  __/   | | |_| | |_) |  __/\__ \
 * \_|  |_|  |_|_| |_| |_|_|\__|_| \_/ \___|   \_/\__, | .__/ \___||___/
 *                                                 __/ | |
 *                                                |___/|_|
 *
 * BRIEF:
 * fixed size types 'non-iso' including (ANSI).
 */
#if defined(TBC_CC_STD_99)
#include <inttypes.h>
/** signed 8 bits **/
typedef int8_t tbc_i8_t;
/** signed 16 bits **/
typedef int16_t tbc_i16_t;
/** signed 32 bits **/
typedef int32_t tbc_i32_t;
/** signed 64 bits **/
typedef int64_t tbc_i64_t;
/** unsigned 8 bits **/
typedef uint8_t tbc_u8_t;
/** unsigned 16 bits **/
typedef uint16_t tbc_u16_t;
/** unsigned 32 bits **/
typedef uint32_t tbc_u32_t;
/** unsigned 64 bits **/
typedef uint64_t tbc_u64_t;
#elif defined(TBC_ARCH_BITS_64)
/** signed 8 bits **/
typedef signed char tbc_i8_t;
/** signed 16 bits **/
typedef signed short tbc_i16_t;
/** signed 32 bits **/
typedef signed int tbc_i32_t;
/** signed 64 bits **/
typedef signed long tbc_i64_t;
/** unsigned 8 bits **/
typedef unsigned char tbc_u8_t;
/** unsigned 16 bits **/
typedef unsigned short tbc_u16_t;
/** unsigned 32 bits **/
typedef unsigned int tbc_u32_t;
/** unsigned 64 bits **/
typedef unsigned long tbc_u64_t;
#elif defined(TBC_ARCH_BITS_32)
/** signed 8 bits **/
typedef signed char tbc_i8_t;
/** signed 16 bits **/
typedef signed short tbc_i16_t;
/** signed 32 bits **/
typedef signed int tbc_i32_t;
/** signed 64 bits **/
typedef signed long long tbc_i64_t;
/** unsigned 8 bits **/
typedef unsigned char tbc_u8_t;
/** unsigned 16 bits **/
typedef unsigned short tbc_u16_t;
/** unsigned 32 bits **/
typedef unsigned int tbc_u32_t;
/** unsigned 64 bits **/
typedef unsigned long long tbc_u64_t;
#elif defined(TBC_ARCH_BITS_16)
/** signed 8 bits **/
typedef signed char tbc_i8_t;
/** signed 16 bits **/
typedef signed short tbc_i16_t;
/** signed 32 bits **/
typedef signed int tbc_i32_t;
/** unsigned 8 bits **/
typedef unsigned char tbc_u8_t;
/** unsigned 16 bits **/
typedef unsigned short tbc_u16_t;
/** unsigned 32 bits **/
typedef unsigned int tbc_u32_t;
#elif defined(TBC_ARCH_BITS_8)
/** signed 8 bits **/
typedef signed char tbc_i8_t;
/** signed 16 bits **/
typedef signed int tbc_i16_t;
/** signed 32 bits **/
typedef signed long tbc_i32_t;
/** unsigned 8 bits **/
typedef unsigned char tbc_u8_t;
/** unsigned 16 bits **/
typedef unsigned int tbc_u16_t;
/** unsigned 32 bits **/
typedef unsigned long tbc_u32_t;
#endif

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

/** application 3bc id (depends of cpu size)**/
#if defined(TBC_ARCH_BITS_64)
typedef tbc_u64_t app_3bc_id;
#elif defined(TBC_ARCH_BITS_32) && !defined(TBC_OPT_COMPACT)
typedef tbc_u32_t app_3bc_id;
#elif defined(TBC_ARCH_BITS_32) || defined(TBC_ARCH_BITS_16)
typedef tbc_u16_t app_3bc_id;
#elif defined(TBC_ARCH_BITS_8)
typedef tbc_u8_t app_3bc_id;
#else
typedef tbc_u16_t app_3bc_id;
#endif

/** FILE/STREAM/INTERFACE TYPES **/
typedef FILE file_t;

enum stream_type_e {
    STREAM_TYPE_NONE = 0,
    STREAM_TYPE_SILENT,
    STREAM_TYPE_ARDUINO_SERIAL,
    STREAM_TYPE_ARDUINO_FILE,
    STREAM_TYPE_COMPUTER_STD,
    STREAM_TYPE_COMPUTER_FILE,
    STREAM_TYPE_FUNCTION_CALL,
    STREAM_TYPE_CLONE_TTY
};

union stream_file_u {
    file_t* file;
    file_t* stream;
    void (*lambda)(char*);
    struct tty_3bc_s* tty;
};

struct tty_3bc_s {
    enum stream_type_e type;
    union stream_file_u io;
};

/** FSM INTERRUPTS **/
enum fsm_3bc_e {
    FSM_3BC_DEFAULT = 0,
    FSM_3BC_READING,
    FSM_3BC_RUNNING,
    FSM_3BC_WAITING,
    FSM_3BC_IO_READ,
    FSM_3BC_IO_SEND,
    FSM_3BC_EXITING,
    FSM_3BC_STOPED
};

/** DS PROCEDURE LIFO **/
struct procedure_3bc_s {
    label_3bc_t label;
    struct line_node_s* remember;
    struct procedure_3bc_s* prev;
};

/** AUXILIARY MEMORY **/
enum sleep_3bc_e {
    SLEEP_3BC_NONE = 0,
    SLEEP_3BC_REAL_TICK,
    SLEEP_3BC_FAKE_TICK,
    SLEEP_3BC_MICROSECONDS,
    SLEEP_3BC_MILLISECONDS,
    SLEEP_3BC_SECONDS
};

struct buffer_s {
    char* storage;
    unsigned int size;
};

union cache_l1_u {
    enum sleep_3bc_e sleep_mode;
};

union cache_l2_u {
    unsigned long sleep_period;
};

union cache_l3_u {
    struct buffer_s buffer;
    unsigned long sleep_called;
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
    enum fsm_3bc_e state;
    data_aux_3bc_t mem_aux;
    cpumode_3bc_t cpu_mode;
    enum error_3bc_e error_code;
    union cache_l1_u cache_l1;
    union cache_l2_u cache_l2;
    union cache_l3_u cache_l3;
    struct tty_3bc_s tty_input;
    struct tty_3bc_s tty_debug;
    struct tty_3bc_s tty_output;
    struct tty_3bc_s tty_source;
    struct tty_3bc_s tty_keylog;
    struct tty_3bc_s tty_error;
    struct program_3bc_s program;
    struct memory_3bc_s memory;
};

typedef void (*function_3bc_t)(
    struct app_3bc_s* const, register_3bc_t, address_3bc_t, data_3bc_t);

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
