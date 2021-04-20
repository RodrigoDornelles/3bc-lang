#include "3bc.h"

#define MODE_EMPUTY             0x00
#define MODE_DEBUG              0x01
#define MODE_STRING             0x02
#define MODE_INPUT              0x03
#define MODE_INPUT_SILENT       0x04
#define MODE_INPUT_PASSWORD     0x05
#define MODE_MEMORY             0x06
#define MODE_PROTECTED          0x07
#define MODE_MEMORY_AUX         0x08
#define MODE_JUMP               0x09
#define MODE_CUSTOM_1           0x0A
#define MODE_MATH_SUM           0x0B
#define MODE_MATH_SUB           0x0C
#define MODE_MATH_MUL           0x0D
#define MODE_MATH_DIV           0x0E
#define MODE_MATH_MOD           0x0F
#define MODE_MATH_POWER         0x10
#define MODE_MATH_ROOT          0x11
#define MODE_MATH_PERCENTAGE    0x12
#define MODE_MATH_ABS           0x13
#define MODE_CUSTOM_2           0x14
#define MODE_HELPER_AVARAGE     0x15
#define MODE_HELPER_SORT        0x16
#define MODE_HELPER_MAX         0x17
#define MODE_HELPER_MIN         0x18

#define NILL 0b000
#define MODE 0b111

#define STRI 0b001
#define FREE 0b001
#define MATH 0b001
#define GOTO 0b001

#define STRC 0b010
#define ALOC 0b010
#define FGTO 0b010

#define STRO 0b011 
#define TCFG 0b011
#define PULL 0b011  
#define ZGTO 0b011

#define STRX 0b100
#define PGTO 0b100
#define TMAX 0b100
#define SPIN 0b100

#define TMIN 0b101
#define NGTO 0b101
#define PUSH 0b101

/**
 * case of separate compilation in different statistical libraries,
 * only FILE: tape_program.c must know this variable
 * 
 * (required for avr compiler in arduino ide)
 */
#ifdef _3BC_REQUIRE_INSTRUCTIONS
void (*instructions[][8]) (PARAMS_DEFINE) = {
    CPU_PACK0(),
    CPU_PACK4(cpu_debug_stri, cpu_debug_strc, cpu_debug_stro, cpu_debug_strx),
    CPU_PACK4(cpu_string_stri, cpu_string_strc, cpu_string_stro, cpu_string_strx),
    CPU_PACK4(cpu_input_stri, cpu_input_strc, cpu_input_stro, cpu_input_strx),
    CPU_PACK4(cpu_input_silent_stri, cpu_input_silent_strc, cpu_input_silent_stro, cpu_input_silent_strx),
    CPU_PACK4(cpu_input_password_stri, cpu_input_password_strc, cpu_input_password_stro, cpu_input_password_strx),
    CPU_PACK5(cpu_memory_free, cpu_memory_aloc, cpu_memory_tcfg, cpu_memory_tmax, cpu_memory_tmin),
    CPU_PACK_PROTECTED(),
    CPU_PACK5(cpu_memory_aux_free, cpu_memory_aux_aloc, cpu_memory_aux_pull, cpu_memory_aux_spin, cpu_memory_aux_push),
    CPU_PACK5(cpu_jump_goto, cpu_jump_fgto, cpu_jump_zgto, cpu_jump_pgto, cpu_jump_ngto),
    CPU_PACK_RESERVED(),
    CPU_PACK1(cpu_math_sum),
    CPU_PACK1(cpu_math_sub),
    CPU_PACK1(cpu_math_mul),
    CPU_PACK1(cpu_math_div),
    CPU_PACK1(cpu_math_mod),
    CPU_PACK1(cpu_math_power),
    CPU_PACK1(cpu_math_root),
    CPU_PACK1(cpu_math_percentage),
    CPU_PACK1(cpu_math_abs),
    CPU_PACK_RESERVED(),
    CPU_PACK1(cpu_helper_average),
    CPU_PACK1(cpu_helper_sort),
    CPU_PACK1(cpu_helper_max),
    CPU_PACK1(cpu_helper_min)
};
#endif