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

#ifndef AUX
#define AUX (driver_accumulator_get(app))
#endif

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
    (0b00000010) /** TODO: trust in over/under flow                            \
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
        driver_tty_output_raw(app, app->tty_error, (b));                       \
        break;
#define LLRBT_IS_RED(n) (n == NULL ? false : n->color == LLRBT_RED)
#define POINTER(a) (driver_memory_pointer(app, a))
#define BITFIELD_HAS(a, b) ((b) == ((a) & (b)))
/**
 * PARAMTERS MACROS
 */
#define PARAMS_DEFINE                                                          \
    struct app_3bc_s *const app, register_3bc_t reg, address_3bc_t address,    \
        data_3bc_t value
#define VALIDATE_NOT_DUALITY                                                   \
    if (address != 0 && value != 0)                                            \
        driver_program_error(app, ERROR_PARAM_DUALITY);
#define VALIDATE_NOT_ADRESS                                                    \
    if (address != 0)                                                          \
        driver_program_error(app, ERROR_PARAM_BLOCKED_ADDRESS);
#define VALIDATE_NOT_VALUES                                                    \
    if (value != 0)                                                            \
        driver_program_error(app, ERROR_PARAM_BLOCKED_VALUE);
#define VALIDATE_NOT_NEGATIVES                                                 \
    if (value < 0 || driver_memory_data_get(app, address) < 0 || AUX < 0)      \
        driver_program_error(app, ERROR_NUMBER_NEGATIVE);
#define REQUIRED_ADDRESS                                                       \
    if (address == 0)                                                          \
        driver_program_error(app, ERROR_PARAM_REQUIRE_ADDRESS);
#define REQUIRED_VALUE                                                         \
    if (value == 0)                                                            \
        driver_program_error(app, ERROR_PARAM_REQUIRE_VALUE);
#define REQUIRED_ANY                                                           \
    if (value == 0 && address == 0)                                            \
        driver_program_error(app, ERROR_PARAM_REQUIRE_ANY);

/**
 * INSTRUCTIONS PACK MACROS
 */
#define CPU_PACK_ZEROMODE(mode)                                                \
    case ((mode * 7) + 1):                                                     \
    case ((mode * 7) + 2):                                                     \
    case ((mode * 7) + 3):                                                     \
    case ((mode * 7) + 4):                                                     \
    case ((mode * 7) + 5):                                                     \
    case ((mode * 7) + 6):                                                     \
        cpu_not_mode(app, reg, address, value);                                \
        break;
#define CPU_PACK_RESERVED(mode)                                                \
    case ((mode * 7) + 1):                                                     \
    case ((mode * 7) + 2):                                                     \
    case ((mode * 7) + 3):                                                     \
    case ((mode * 7) + 4):                                                     \
    case ((mode * 7) + 5):                                                     \
    case ((mode * 7) + 6):                                                     \
        cpu_mode_reserved(app, reg, address, value);                           \
        break;
#define CPU_PACK1(mode, a)                                                     \
    case ((mode * 7) + 1):                                                     \
        a(app, reg, address, value);                                           \
        break;
#define CPU_PACK2(mode, a, b)                                                  \
    case ((mode * 7) + 1):                                                     \
        a(app, reg, address, value);                                           \
        break;                                                                 \
    case ((mode * 7) + 2):                                                     \
        b(app, reg, address, value);                                           \
        break;
#define CPU_PACK3(mode, a, b, c)                                               \
    case ((mode * 7) + 1):                                                     \
        a(app, reg, address, value);                                           \
        break;                                                                 \
    case ((mode * 7) + 2):                                                     \
        b(app, reg, address, value);                                           \
        break;                                                                 \
    case ((mode * 7) + 3):                                                     \
        c(app, reg, address, value);                                           \
        break;
#define CPU_PACK4(mode, a, b, c, d)                                            \
    case ((mode * 7) + 1):                                                     \
        a(app, reg, address, value);                                           \
        break;                                                                 \
    case ((mode * 7) + 2):                                                     \
        b(app, reg, address, value);                                           \
        break;                                                                 \
    case ((mode * 7) + 3):                                                     \
        c(app, reg, address, value);                                           \
        break;                                                                 \
    case ((mode * 7) + 4):                                                     \
        d(app, reg, address, value);                                           \
        break;
#define CPU_PACK5(mode, a, b, c, d, e)                                         \
    case ((mode * 7) + 1):                                                     \
        a(app, reg, address, value);                                           \
        break;                                                                 \
    case ((mode * 7) + 2):                                                     \
        b(app, reg, address, value);                                           \
        break;                                                                 \
    case ((mode * 7) + 3):                                                     \
        c(app, reg, address, value);                                           \
        break;                                                                 \
    case ((mode * 7) + 4):                                                     \
        d(app, reg, address, value);                                           \
        break;                                                                 \
    case ((mode * 7) + 5):                                                     \
        e(app, reg, address, value);                                           \
        break;
#define CPU_PACK6(mode, a, b, c, d, e, f)                                      \
    case ((mode * 7) + 1):                                                     \
        a(app, reg, address, value);                                           \
        break;                                                                 \
    case ((mode * 7) + 2):                                                     \
        b(app, reg, address, value);                                           \
        break;                                                                 \
    case ((mode * 7) + 3):                                                     \
        c(app, reg, address, value);                                           \
        break;                                                                 \
    case ((mode * 7) + 4):                                                     \
        d(app, reg, address, value);                                           \
        break;                                                                 \
    case ((mode * 7) + 5):                                                     \
        e(app, reg, address, value);                                           \
        break;                                                                 \
    case ((mode * 7) + 6):                                                     \
        f(app, reg, address, value);                                           \
        break;

/**
 * USER MACROS
 */
#define lang_3bc_update driver_interrupt
#define lang_3bc_init driver_power_init
#define lang_3bc_line ds_program_fifo_line_add
#define lang_3bc_print(a, t, l)                                                \
    ;                                                                          \
    a->t.type = STREAM_TYPE_FUNCTION_CALL;                                     \
    a->t.io.lambda = l;
#define lang_3bc_custom driver_custom_set
