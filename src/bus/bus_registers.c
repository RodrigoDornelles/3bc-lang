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
 * Header refers to register opcodes.
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


#include "3bc.h"

/**
 * case of separate compilation in different statistical libraries,
 * only FILE: ds_program_fifo.c must know this variable
 *
 * (required for avr compiler in arduino ide)
 */
void instruction_3bc(struct app_3bc_s* const app)
{
    register_3bc_t reg = app->cache_l0.rx;
    address_3bc_t address = app->cache_l0.ry;
    data_3bc_t value = app->cache_l0.rz;
    
    if (reg == 0) {
        cpu_null(app, 0, 0, 0);
    } else if (reg == 7) {
        cpu_mode(app, reg, address, value);
    }
    /** CPU MODES ADD REGISTER PACKAGES **/
    else
        switch ((app->cpu_mode * 7) + reg) {
        /** prevent enter in invalid cpu mode **/
        default:
            cpu_not_exist(app, 0, 0, 0);
            CPU_PACK_ZEROMODE(TBC_MODE_EMPUTY);
            CPU_PACK5(TBC_MODE_DEBUG, cpu_string_debug, cpu_string_debug,
                cpu_string_debug, cpu_string_debug, cpu_string_debug);
            CPU_PACK5(TBC_MODE_STRING, cpu_string_output, cpu_string_output,
                cpu_string_output, cpu_string_output, cpu_string_output);
            CPU_PACK5(TBC_MODE_INPUT, cpu_string_input, cpu_string_input,
                cpu_string_input, cpu_string_input, cpu_string_input);
            CPU_PACK5(TBC_MODE_INPUT_SILENT, cpu_string_input_silent,
                cpu_string_input_silent, cpu_string_input_silent,
                cpu_string_input_silent, cpu_string_input_silent);
            CPU_PACK5(TBC_MODE_INPUT_PASSWORD, cpu_string_input_password,
                cpu_string_input_password, cpu_string_input_password,
                cpu_string_input_password, cpu_string_input_password);
            CPU_PACK4(TBC_MODE_MEMORY, cpu_memory_free, cpu_memory_aloc,
                cpu_memory_moff, cpu_memory_muse);
            CPU_PACK5(TBC_MODE_MEMORY_PTR, cpu_memory_ptr_free, cpu_memory_ptr_aloc,
                cpu_memory_ptr_pull, cpu_memory_ptr_spin, cpu_memory_ptr_push);
            CPU_PACK5(TBC_MODE_MEMORY_AUX, cpu_memory_aux_free, cpu_memory_aux_aloc,
                cpu_memory_aux_pull, cpu_memory_aux_spin, cpu_memory_aux_push);
            CPU_PACK5(TBC_MODE_JUMP, cpu_jump_goto, cpu_jump_fgto, cpu_jump_zgto,
                cpu_jump_pgto, cpu_jump_ngto);
            CPU_PACK_RESERVED(TBC_MODE_CUSTOM_1);
            CPU_PACK1(TBC_MODE_MATH_SUM, cpu_math_sum);
            CPU_PACK1(TBC_MODE_MATH_SUB, cpu_math_sub);
            CPU_PACK1(TBC_MODE_MATH_MUL, cpu_math_mul);
            CPU_PACK1(TBC_MODE_MATH_DIV, cpu_math_div);
            CPU_PACK1(TBC_MODE_MATH_MOD, cpu_math_mod);
            CPU_PACK1(TBC_MODE_MATH_POWER, cpu_math_power);
            CPU_PACK1(TBC_MODE_MATH_ROOT, cpu_math_root);
            CPU_PACK1(TBC_MODE_MATH_ABS, cpu_math_abs);
            CPU_PACK4(TBC_MODE_MATH_MUL_ADD, cpu_math_mul_add, cpu_math_mul_add,
                cpu_math_mul_add, cpu_math_mul_add);
            CPU_PACK_RESERVED(TBC_MODE_CUSTOM_2);
            CPU_PACK1(TBC_MODE_BITWISE_NOT, cpu_bitwise_not);
            CPU_PACK1(TBC_MODE_BITWISE_AND, cpu_bitwise_and);
            CPU_PACK1(TBC_MODE_BITWISE_OR, cpu_bitwise_or);
            CPU_PACK1(TBC_MODE_BITWISE_XOR, cpu_bitwise_xor);
            CPU_PACK1(TBC_MODE_BITWISE_NAND, cpu_bitwise_nand);
            CPU_PACK1(TBC_MODE_BITWISE_NOR, cpu_bitwise_nor);
            CPU_PACK1(TBC_MODE_BITWISE_XNOR, cpu_bitwise_xnor);
            CPU_PACK1(TBC_MODE_BITWISE_LEFT, cpu_bitwise_left);
            CPU_PACK1(TBC_MODE_BITWISE_RIGHT, cpu_bitwise_right);
            CPU_PACK_RESERVED(TBC_MODE_CUSTOM_3);
            CPU_PACK1(TBC_MODE_BOOLEAN_NOT, cpu_bool_not);
            CPU_PACK1(TBC_MODE_BOOLEAN_AND, cpu_bool_and);
            CPU_PACK1(TBC_MODE_BOOLEAN_OR, cpu_bool_or);
            CPU_PACK1(TBC_MODE_BOOLEAN_XOR, cpu_bool_xor);
            CPU_PACK1(TBC_MODE_BOOLEAN_NAND, cpu_bool_nand);
            CPU_PACK1(TBC_MODE_BOOLEAN_NOR, cpu_bool_nor);
            CPU_PACK1(TBC_MODE_BOOLEAN_XNOR, cpu_bool_xnor);
            CPU_PACK1(TBC_MODE_MATH_LOG_BASE, cpu_math_logb);
            CPU_PACK1(TBC_MODE_MATH_LOG_NATURAL, cpu_math_logn);
            CPU_PACK_RESERVED(TBC_MODE_CUSTOM_4);
            CPU_PACK5(TBC_MODE_PROCEDURE_RET, cpu_procedure_back,
                cpu_procedure_fret, cpu_procedure_zret, cpu_procedure_pret,
                cpu_procedure_nret);
            CPU_PACK5(TBC_MODE_PROCEDURE, cpu_procedure_call, cpu_procedure_fcal,
                cpu_procedure_zcal, cpu_procedure_pcal, cpu_procedure_ncal);
            CPU_PACK5(TBC_MODE_SLEEP, cpu_sleep_real, cpu_sleep_fake,
                cpu_sleep_micr, cpu_sleep_mili, cpu_sleep_seco);
        }
}
