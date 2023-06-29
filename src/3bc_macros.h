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
 * Header refers to usefull macros.
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

/**
 * CONSTS MACROS
 */
#define LLRBT_BLACK (false)
#define LLRBT_RED (true)

#ifndef LABEL_HASH_SIZE
#ifdef TBC_OPT_COMPACT
#define LABEL_HASH_SIZE (8)
#else
#define LABEL_HASH_SIZE (128)
#endif
#endif

#ifndef GET_ANY_PARAM
#define GET_ANY_PARAM (address ? driver_memory_data_get(app, address) : value)
#endif

#define MEM_CONFIG_RESERVED (0b00000001) /** unused **/
#define MEM_CONFIG_FLOW_SAFE                                                   \
    (0b00000010) /** @todo trust in over/under flow                            \
                  **/
#define MEM_CONFIG_GPIO_SEND (0b00000100) /** digital output **/
#define MEM_CONFIG_GPIO_READ (0b00001000) /** digital input **/
#define MEM_CONFIG_GPIO_PULL (0b00010000) /** pullup input **/
#define MEM_CONFIG_GPIO_ANAL (0b00100000) /** analogic/pwd **/

/**
 * FUNCTIONS MACROS
 */
#define ERROR_LOG_3BC(a, b)                                                    \
    case (a):                                                                  \
        driver_tty_output_raw(app, &app->cout.tty_error, (b));                       \
        break;
#define LLRBT_IS_RED(n) (n == NULL ? false : n->color == LLRBT_RED)
#define BITFIELD_HAS(a, b) ((b) == ((a) & (b)))
/**
 * PARAMTERS MACROS
 */
#define PARAMS_DEFINE                                                          \
    struct app_3bc_s *const app, register_3bc_t reg, address_3bc_t address,    \
        data_3bc_t value
/**
 * USER MACROS
 */
#define lang_3bc_update driver_interrupt
#define lang_3bc_init driver_power_init
#define lang_3bc_line ds_program_fifo_line_add
#define lang_3bc_print(a, t, l)                                                \
    ;                                                                          \
    a->cout.t.type = STREAM_TYPE_FUNCTION_CALL;                                \
    a->cout.t.io.lambda.ptr = (void*) l;
#define lang_3bc_custom driver_custom_set
