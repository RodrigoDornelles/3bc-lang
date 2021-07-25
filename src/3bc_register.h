#include "3bc.h"

#define MODE_EMPUTY             (0)
#define MODE_DEBUG              (1)
#define MODE_STRING             (2)
#define MODE_INPUT              (3)
#define MODE_INPUT_SILENT       (4)
#define MODE_INPUT_PASSWORD     (5)
#define MODE_MEMORY             (6)
#define MODE_MEMORY_PTR         (7)
#define MODE_MEMORY_AUX         (8)
#define MODE_JUMP               (9)
#define MODE_CUSTOM_1           (10)
#define MODE_MATH_SUM           (11)
#define MODE_MATH_SUB           (12)
#define MODE_MATH_MUL           (13)
#define MODE_MATH_DIV           (14)
#define MODE_MATH_MOD           (15)
#define MODE_MATH_POWER         (16)
#define MODE_MATH_ROOT          (17)
#define MODE_MATH_ABS           (18)
#define MODE_MATH_NEGATIVE      (19)
#define MODE_CUSTOM_2           (20)
#define MODE_HELPER_AVARAGE     (21)
#define MODE_HELPER_SIGN        (22)
#define MODE_HELPER_MAX         (23)
#define MODE_HELPER_MIN         (24)
#define MODE_HELPER_PERCENTAGE  (25)
#define MODE_HELPER_REVERSE     (26)
#define MODE_HELPER_LOG2        (27)
#define MODE_HELPER_LOG10       (28)
#define MODE_HELPER_MUL_ADD     (29)
#define MODE_CUSTOM_3           (30)
#define MODE_MEMORY_SORT        (31)

#define NILL 0b000
#define MODE 0b111

#define STRI 0b001
#define FREE 0b001
#define MATH 0b001
#define GOTO 0b001
#define NB02 0b001

#define STRC 0b010
#define ALOC 0b010
#define FGTO 0b010
#define NB08 0b010

#define STRO 0b011 
#define MOFF 0b011
#define PULL 0b011  
#define ZGTO 0b011
#define NB10 0B011

#define STRX 0b100
#define PGTO 0b100
#define MUSE 0b100
#define SPIN 0b100
#define NB16 0b100

#define MMAX 0b101
#define NGTO 0b101
#define PUSH 0b101

#define MMIN 0b110
/**
 * case of separate compilation in different statistical libraries,
 * only FILE: tape_program.c must know this variable
 * 
 * (required for avr compiler in arduino ide)
 */
#ifdef _3BC_SCU_FIX
function_3bc_t instructions(cpumode_3bc_t mode, register_3bc_t reg)
{
    #ifdef _3BC_COMPACT
    switch (mode)
    {
        /** prevent enter in invalid cpu mode **/
        default: driver_program_error(ERROR_INVALID_CPU);
    #else
        const static function_3bc_t _instructions[][8] = {
    #endif
        /** CPU MODES ADD REGISTER PACKAGES **/
        CPU_PACK_ZEROMODE(MODE_EMPUTY)
        CPU_PACK4(MODE_DEBUG, cpu_debug_stri, cpu_debug_strc, cpu_debug_stro, cpu_debug_strx)
        CPU_PACK4(MODE_STRING, cpu_string_stri, cpu_string_strc, cpu_string_stro, cpu_string_strx)
        CPU_PACK4(MODE_INPUT, cpu_input_stri, cpu_input_strc, cpu_input_stro, cpu_input_strx)
        CPU_PACK4(MODE_INPUT_SILENT, cpu_input_silent_stri, cpu_input_silent_strc, cpu_input_silent_stro, cpu_input_silent_strx)
        CPU_PACK4(MODE_INPUT_PASSWORD, cpu_input_password_stri, cpu_input_password_strc, cpu_input_password_stro, cpu_input_password_strx)
        CPU_PACK6(MODE_MEMORY, cpu_memory_free, cpu_memory_aloc, cpu_memory_moff, cpu_memory_muse, cpu_memory_mmax, cpu_memory_mmin)
        CPU_PACK5(MODE_MEMORY_PTR, cpu_memory_ptr_free, cpu_memory_ptr_aloc, cpu_memory_ptr_pull, cpu_memory_ptr_spin, cpu_memory_ptr_push)
        CPU_PACK5(MODE_MEMORY_AUX, cpu_memory_aux_free, cpu_memory_aux_aloc, cpu_memory_aux_pull, cpu_memory_aux_spin, cpu_memory_aux_push)
        CPU_PACK5(MODE_JUMP,cpu_jump_goto, cpu_jump_fgto, cpu_jump_zgto, cpu_jump_pgto, cpu_jump_ngto)
        CPU_PACK_RESERVED(MODE_CUSTOM_1)
        CPU_PACK1(MODE_MATH_SUM, cpu_math_sum)
        CPU_PACK1(MODE_MATH_SUB, cpu_math_sub)
        CPU_PACK1(MODE_MATH_MUL, cpu_math_mul)
        CPU_PACK1(MODE_MATH_DIV, cpu_math_div)
        CPU_PACK1(MODE_MATH_MOD, cpu_math_mod)
        CPU_PACK1(MODE_MATH_POWER, cpu_math_power)
        CPU_PACK1(MODE_MATH_ROOT, cpu_math_root)
        CPU_PACK1(MODE_MATH_ABS, cpu_math_abs)
        CPU_PACK1(MODE_MATH_NEGATIVE, cpu_math_negative)
        CPU_PACK_RESERVED(MODE_CUSTOM_2)
        CPU_PACK1(MODE_HELPER_AVARAGE, cpu_helper_average)
        CPU_PACK1(MODE_HELPER_SIGN, cpu_helper_sign)
        CPU_PACK1(MODE_HELPER_MAX, cpu_helper_max)
        CPU_PACK1(MODE_HELPER_MIN, cpu_helper_min)
        CPU_PACK1(MODE_HELPER_PERCENTAGE, cpu_helper_percentage)
        CPU_PACK4(MODE_HELPER_REVERSE, cpu_helper_reverse, cpu_helper_reverse, cpu_helper_reverse, cpu_helper_reverse)
        CPU_PACK1(MODE_HELPER_LOG2, cpu_helper_log2)
        CPU_PACK1(MODE_HELPER_LOG10, cpu_helper_log10)
        CPU_PACK4(MODE_HELPER_MUL_ADD, cpu_helper_mul_add, cpu_helper_mul_add, cpu_helper_mul_add, cpu_helper_mul_add)
        CPU_PACK_RESERVED(MODE_CUSTOM_3)
        CPU_PACK1(MODE_MEMORY_SORT, cpu_helper_sort)
    }
    #ifndef _3BC_COMPACT
    /** close array **/
    ;
    /** out of bounds cpu mode **/
    if (mode < 0 || mode >= (sizeof(_instructions)/sizeof(_instructions[0]))) {
       driver_program_error(ERROR_INVALID_CPU);
    }
    /** out of bounds cpu register **/
    if (reg < 0 || reg >= 8) {
        driver_program_error(ERROR_INVALID_REGISTER);
    }
    return _instructions[mode][reg];
    #endif
}
#endif