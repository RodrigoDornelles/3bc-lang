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
 * Code refers customization of registers by the user.
 *
 * DATASTRUCT:
 * Dynamic Array
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

#if !defined(TBC_SCU_OPTIONAL_FIX)
#if !defined(TBC_CUSTOM)
void driver_custom_call(struct app_3bc_s* const app, register_3bc_t reg,
    address_3bc_t address, data_3bc_t value)
{
    driver_program_error(app, ERROR_CPU_RESERVED);
}

#else
function_3bc_t* custom_funcs = NULL;
unsigned char last_func = 0;

void driver_custom_set(struct app_3bc_s* const app, cpumode_3bc_t cpu_mode,
    register_3bc_t reg, function_3bc_t lambda)
{
    unsigned char atual_func = ((cpu_mode / 10) - 1) * 6 + reg;

    /** expand array of functions **/
    if (custom_funcs == NULL || last_func <= atual_func) {
        function_3bc_t* new_array = (function_3bc_t*)realloc(
            custom_funcs, sizeof(function_3bc_t) * atual_func + 1);

        if (new_array == NULL) {
            driver_program_error(app, ERROR_OUT_OF_MEMORY);
        }

        /** clean wild pointers **/
        while (last_func <= atual_func)
        {
            new_array[last_func] = NULL;
            ++last_func;
        }

        custom_funcs = new_array;
    }

    /** update custom function **/
    custom_funcs[atual_func] = lambda;
}

void driver_custom_call(struct app_3bc_s* const app, register_3bc_t reg,
    address_3bc_t address, data_3bc_t value)
{
    unsigned char atual_func = ((app->cpu_mode / 10) - 1) * 6 + reg;

    /** custom function not found **/
    if (custom_funcs == NULL || custom_funcs[atual_func] == NULL
        || atual_func >= last_func) {
        driver_program_error(app, ERROR_CPU_RESERVED);
    }

    custom_funcs[atual_func](app, reg, address, value);
}
#endif
#endif
