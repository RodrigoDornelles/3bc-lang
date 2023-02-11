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
 * Code refers registers for the arithmetic logic unit.
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

#define TBC_SOURCE_ENTRY
#include "3bc.h"

void cpu_math_sum(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    driver_accumulator_set(app, AUX + GET_ANY_PARAM);
}

void cpu_math_sub(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    driver_accumulator_set(app, AUX - GET_ANY_PARAM);
}

void cpu_math_mul(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    driver_accumulator_set(app, AUX * GET_ANY_PARAM);
}

void cpu_math_div(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    {
        data_3bc_t divisor = GET_ANY_PARAM;
        if (divisor == 0) {
            driver_program_error(app, ERROR_NUMBER_ZERO);
        } else {
            driver_accumulator_set(app, AUX / divisor);
        }
    }
}

void cpu_math_mod(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    driver_accumulator_set(app, AUX % GET_ANY_PARAM);
}

void cpu_math_power(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
#if defined(TBC_NOT_MATH)
    driver_program_error(app, ERROR_UNSUPPORTED);
#else
    /** TODO: remove this "gambiarra" tecnical debt **/
    driver_accumulator_set(app,
        (data_aux_3bc_t)trunc(pow((double)(AUX), (double)(GET_ANY_PARAM))));
#endif
}

void cpu_math_root(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
#if defined(TBC_NOT_MATH)
    driver_program_error(app, ERROR_UNSUPPORTED);
#else
    driver_accumulator_set(app,

        (data_aux_3bc_t)trunc(
            pow((double)(AUX), (1 / (double)(GET_ANY_PARAM)))));
#endif
}

void cpu_math_abs(PARAMS_DEFINE)
{
    VALIDATE_NOT_ADRESS
    VALIDATE_NOT_VALUES
    driver_accumulator_set(app, labs(AUX));
}

/**
 * logarithm with base
 */
void cpu_math_logb(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    REQUIRED_ANY
    if (AUX == 0) {
        driver_program_error(app, ERROR_NUMBER_ZERO);
    } else {
        int base = GET_ANY_PARAM;
        switch (base) {
#if !defined(TBC_NOT_MATH)
#if !defined(TBC_NOT_LOG2)
        case 2:
            driver_accumulator_set(
                app, (data_aux_3bc_t)trunc(log2((double)AUX)));
            break;
#endif

#if !defined(TBC_NOT_LOG10)
        case 10:
            driver_accumulator_set(
                app, (data_aux_3bc_t)trunc(log10((double)AUX)));
            break;
#endif
#endif

#if defined(TBC_NOT_LOG) || defined(TBC_NOT_MATH)
        default:
            driver_program_error(app, ERROR_UNSUPPORTED);
#else
        default:
            driver_accumulator_set(app,
                (data_aux_3bc_t)trunc(log((double)AUX) / log((double)base)));
            break;
#endif
        }
    }
}

/**
 * logarithm natural
 */
void cpu_math_logn(PARAMS_DEFINE)
{
    VALIDATE_NOT_ADRESS
    VALIDATE_NOT_VALUES
#if defined(TBC_NOT_MATH)
    /** TODO: support logarithm on 6502 **/
    driver_program_error(app, ERROR_UNSUPPORTED);
#else
    if (AUX == 0) {
        driver_program_error(app, ERROR_NUMBER_ZERO);
    }

    driver_accumulator_set(app, (data_aux_3bc_t)trunc(log((double)AUX)));
#endif
}

void cpu_math_mul_add(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    {
        char base = 0;

        if (reg == NB02) {
            base = 2;
        } else if (reg == NB08) {
            base = 8;
        } else if (reg == NB10) {
            base = 10;
        } else if (reg == NB16) {
            base = 16;
        }

        driver_accumulator_set(app, (AUX * base) + GET_ANY_PARAM);
    }
}