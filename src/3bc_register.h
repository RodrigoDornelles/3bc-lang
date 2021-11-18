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
#define MODE_MATH_MUL_ADD       (19)
#define MODE_CUSTOM_2           (20)
#define MODE_MATH_LOG_BASE      (29)
#define MODE_CUSTOM_3           (30)
#define MODE_BOOLEAN_NOT        (31)
#define MODE_BOOLEAN_AND        (32)
#define MODE_BOOLEAN_OR         (33)
#define MODE_BOOLEAN_XOR        (34)
#define MODE_BOOLEAN_NAND       (35)
#define MODE_BOOLEAN_NOR        (36)
#define MODE_BOOLEAN_XNOR       (37)
#define MODE_MATH_LOG_NATURAL   (39)
#define MODE_CUSTOM_4           (40)
#define MODE_PROCEDURE_RET      (41)
#define MODE_PROCEDURE          (42)
#define MODE_SLEEP              (43)
#define MODE_END                (44)

#define NILL 0b000
#define MODE 0b111

#define STRB 0b001
#define FREE 0b001
#define MATH 0b001
#define GOTO 0b001
#define NB02 0b001
#define CALL 0b001
#define BACK 0b001
#define FAKE 0b001

#define STRO 0b010
#define ALOC 0b010
#define FGTO 0b010
#define NB08 0b010
#define STOP 0b010
#define FRET 0b010
#define FCAL 0b010
#define REAL 0b010

#define STRI 0b011 
#define MOFF 0b011
#define PULL 0b011  
#define ZGTO 0b011
#define NB10 0B011
#define ZRET 0b011
#define ZCAL 0b011
#define MICR 0b011

#define STRX 0b100
#define PGTO 0b100
#define MUSE 0b100
#define SPIN 0b100
#define NB16 0b100
#define PRET 0b100
#define PCAL 0b100
#define MILI 0b100

#define STRC 0b101
#define NGTO 0b101
#define PUSH 0b101
#define NRET 0b101
#define NCAL 0b101
#define SECO 0b101

/**
 * case of separate compilation in different statistical libraries,
 * only FILE: tape_program.c must know this variable
 * 
 * (required for avr compiler in arduino ide)
 */
#ifdef _3BC_SCU_FIX
void instruction_3bc(app_3bc_t app, register_3bc_t reg, address_3bc_t address, data_3bc_t value)
{
    if (reg == 0) {
        cpu_null(app, 0, 0, 0);
    }
    else if (reg == 7) {
        cpu_mode(app, reg, address, value);
    }
    /** CPU MODES ADD REGISTER PACKAGES **/
    else switch ((app->cpu_mode * 7) + reg)
    {
        /** prevent enter in invalid cpu mode **/
        default: cpu_not_exist(app, 0,0,0);
        CPU_PACK_ZEROMODE(MODE_EMPUTY);
        CPU_PACK5(MODE_DEBUG, cpu_string_debug, cpu_string_debug, cpu_string_debug, cpu_string_debug, cpu_string_debug);
        CPU_PACK5(MODE_STRING, cpu_string_output, cpu_string_output, cpu_string_output, cpu_string_output, cpu_string_output);
        CPU_PACK5(MODE_INPUT, cpu_string_input, cpu_string_input, cpu_string_input, cpu_string_input, cpu_string_input);
        CPU_PACK5(MODE_INPUT_SILENT, cpu_string_input_silent, cpu_string_input_silent, cpu_string_input_silent, cpu_string_input_silent, cpu_string_input_silent);
        CPU_PACK5(MODE_INPUT_PASSWORD, cpu_string_input_password, cpu_string_input_password, cpu_string_input_password, cpu_string_input_password, cpu_string_input_password);
        CPU_PACK4(MODE_MEMORY, cpu_memory_free, cpu_memory_aloc, cpu_memory_moff, cpu_memory_muse);
        CPU_PACK5(MODE_MEMORY_PTR, cpu_memory_ptr_free, cpu_memory_ptr_aloc, cpu_memory_ptr_pull, cpu_memory_ptr_spin, cpu_memory_ptr_push);
        CPU_PACK5(MODE_MEMORY_AUX, cpu_memory_aux_free, cpu_memory_aux_aloc, cpu_memory_aux_pull, cpu_memory_aux_spin, cpu_memory_aux_push);
        CPU_PACK5(MODE_JUMP,cpu_jump_goto, cpu_jump_fgto, cpu_jump_zgto, cpu_jump_pgto, cpu_jump_ngto);
        CPU_PACK_RESERVED(MODE_CUSTOM_1);
        CPU_PACK1(MODE_MATH_SUM, cpu_math_sum);
        CPU_PACK1(MODE_MATH_SUB, cpu_math_sub);
        CPU_PACK1(MODE_MATH_MUL, cpu_math_mul);
        CPU_PACK1(MODE_MATH_DIV, cpu_math_div);
        CPU_PACK1(MODE_MATH_MOD, cpu_math_mod);
        CPU_PACK1(MODE_MATH_POWER, cpu_math_power);
        CPU_PACK1(MODE_MATH_ROOT, cpu_math_root);
        CPU_PACK1(MODE_MATH_ABS, cpu_math_abs);
        CPU_PACK4(MODE_MATH_MUL_ADD, cpu_math_mul_add, cpu_math_mul_add, cpu_math_mul_add, cpu_math_mul_add);
        CPU_PACK_RESERVED(MODE_CUSTOM_2);
        /** TODO: boolean bitwise **/
        /** TODO: boolean algebra implication bitwise **/
        CPU_PACK1(MODE_MATH_LOG_BASE, cpu_math_logb);
        CPU_PACK_RESERVED(MODE_CUSTOM_3);
        CPU_PACK1(MODE_BOOLEAN_NOT, cpu_bool_not);
        CPU_PACK1(MODE_BOOLEAN_AND, cpu_bool_and);
        CPU_PACK1(MODE_BOOLEAN_OR, cpu_bool_or);
        CPU_PACK1(MODE_BOOLEAN_XOR, cpu_bool_xor);
        CPU_PACK1(MODE_BOOLEAN_NAND, cpu_bool_nand);
        CPU_PACK1(MODE_BOOLEAN_NOR, cpu_bool_nor);
        CPU_PACK1(MODE_BOOLEAN_XNOR, cpu_bool_xnor);
        /** TODO: boolean algebra implication **/
        CPU_PACK1(MODE_MATH_LOG_NATURAL, cpu_math_logn);
        CPU_PACK_RESERVED(MODE_CUSTOM_4);
        CPU_PACK5(MODE_PROCEDURE_RET, cpu_procedure_back, cpu_procedure_fret, cpu_procedure_zret, cpu_procedure_pret, cpu_procedure_nret);
        CPU_PACK5(MODE_PROCEDURE, cpu_procedure_call, cpu_procedure_fcal, cpu_procedure_zcal, cpu_procedure_pcal, cpu_procedure_ncal);
        CPU_PACK5(MODE_SLEEP, cpu_sleep_real, cpu_sleep_fake, cpu_sleep_micr, cpu_sleep_mili, cpu_sleep_seco);
    }
}
#endif