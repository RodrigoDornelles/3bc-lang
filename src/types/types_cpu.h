#ifndef H_TYPES_CPU_TBC
#define H_TYPES_CPU_TBC

#include "types/types_primitive.h"

typedef struct ___tbc_cpu_s tbc_cpu_st;

/**
 * @short internal CPU registers
 * @brief complete layout of all internal registers that inside
 * of the virtual machine's CPU, this is a highly volatile low-level resource.
 * @warning this requires **advanced programming** skills.
 * 
 * @startuml cpu
 * rectangle "CPU" {
 *  rectangle rx
 *  rectangle ry
 *  rectangle rz
 *  rectangle ra
 *  rectangle rm
 * }
 * @enduml
 */
struct ___tbc_cpu_s {
    /** 
     * @short first column
     * @brief behavior of instruction
     * @note 3 bits
     */
    tbc_u8_t rx;
    /**
     * @short second column 
     * @brief address related of instruction
     * @note 9 bits
     */
    tbc_u16_t ry;
    /** 
     * @short third column
     * @brief constant value of instruction
     * @note 12 bits
     */
    tbc_u16_t rz;
    /**
     * @short cpu mode
     * @brief current context of virtual machine
     */
    tbc_u8_t rm;
    /** 
     * @short accumulator
     * @brief auxiliary memory of logical and arithmetic unity 
     */
    tbc_i16_t ra;
};

#endif
