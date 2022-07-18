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
 * Code refers registers for text manipulation.
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

void cpu_string_debug(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    driver_tty_output(app, app->tty_debug, reg, GET_ANY_PARAM);
}

void cpu_string_output(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    driver_tty_output(app, app->tty_output, reg, GET_ANY_PARAM);
}

void cpu_string_input(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    {
        data_3bc_t aux = driver_tty_input(app, app->tty_input, reg);
        driver_accumulator_set(app, aux);
        driver_memory_data_set(app, address, aux);
        driver_tty_output(app, app->tty_keylog, reg, aux);
    }
}

void cpu_string_input_silent(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    {
        data_3bc_t aux = driver_tty_input(app, app->tty_input, reg);
        driver_accumulator_set(app, aux);
        driver_memory_data_set(app, address, aux);
    }
}

void cpu_string_input_password(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    {
        data_3bc_t aux = driver_tty_input(app, app->tty_input, reg);
        driver_accumulator_set(app, aux);
        driver_memory_data_set(app, address, aux);
        driver_tty_output(app, app->tty_keylog, STRC, '*');
    }
}
