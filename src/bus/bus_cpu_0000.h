#ifndef H_BUS_CPU_0000_TBC
#define H_BUS_CPU_0000_TBC

#include "3bc_types.h"

typedef struct ___layout_cpu_s tbc_layout_cpu_st;

/**
 * @param size number of instructions in cpu mode
 * @param opcode function pointers to instructions
 * @param errors permissions of each instruction
 * @li bit 0 ry is required
 * @li bit 1 rz is required
 * @li bit 2 rx is forbidden
 * @li bit 3 rz is forbidden
 * @note bit 0 + bit 2 is duality (allowed zero)
 * @note bit 1 + bit 3 is duality (non zero)
 * @see constants in @ref macros_consts.h 
 */
struct ___layout_cpu_s {
    const tbc_u8_t size;
    const tbc_method_ft* opcodes;
    const tbc_u8_t* errors;
};

/**
 * @brief number of CPU Modes in processor unit layout.
 */
extern const tbc_u8_t tbc_layout_cpu_modes;

/**
 * @brief layout of functions
 * @relates struct ___layout_cpu_s
 */
extern const tbc_layout_cpu_st* tbc_layout_cpu_funcs;

#endif
