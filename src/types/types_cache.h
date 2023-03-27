#ifndef H_TYPES_CACHE_TBC
#define H_TYPES_CACHE_TBC

#include "types_fsm.h"
#include "types_syscall.h"

typedef struct ___tbc_cache_l0_s tbc_cache_l0_st;

struct ___tbc_dynamic_buffer_s {
    char* storage;
    unsigned int size;
};

struct ___tbc_fixed_buffer_s {
    char storage[7];
    tbc_u8_t size;
};

/**
 * @short out of cache internal registers
 * @brief complete layout of all internal registers that inside
 * of the virtual machine's CPU, this is a highly volatile low-level resource.
 * @warning this requires **advanced programming** skills.
 * 
 * @startuml cache_l0
 * rectangle "CPU Cache Lv 0" {
 *  rectangle rx
 *  rectangle ry
 *  rectangle rz
 *  rectangle ra
 *  rectangle rm
 * }
 * @enduml
 */
struct ___tbc_cache_l0_s {
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

union cache_l1_u {
    tbc_sleep_et sleep_mode;
    /** system call id */
    tbc_syscall_et syscall;
    /** use for conditionals (same cycle) */
    bool is; /**< @todo remove **/
};

union cache_l2_u {
    unsigned long sleep_period;
    tbc_tty_st* tty;
};

union cache_l3_u {
    /** fixed buffer */
    struct ___tbc_fixed_buffer_s fixbuf;
    /** dynamic buffer */
    struct ___tbc_dynamic_buffer_s buffer;
    /** auxilary waiting interrupt **/
    unsigned long sleep_called;
};

#endif
