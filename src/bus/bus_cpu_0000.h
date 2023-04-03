#ifndef H_BUS_CPU_0000_TBC
#define H_BUS_CPU_0000_TBC

#include "3bc_types.h"

typedef struct ___layout_cpu_s tbc_layout_cpu_st;

struct ___layout_cpu_s {
    tbc_u8_t* size;
    tbc_method_ft** opcodes;
};

/**
 * @brief number of CPU Modes in processor unit layout.
 */
extern const tbc_u8_t tbc_layout_cpu_modes;

/**
 * @brief size of CPU Modes in processor unit layout. (bytes)
 */
extern const tbc_size_t tbc_layout_cpu_bytes;

/**
 * @brief layout of functions
 */
extern const tbc_layout_cpu_st* tbc_layout_cpu_funcs;

#endif
