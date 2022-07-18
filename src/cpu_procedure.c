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
 * Code refers registers for calling procedures.
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

void cpu_procedure_call(PARAMS_DEFINE)
{
    REQUIRED_VALUE
    VALIDATE_NOT_ADRESS
    ds_procedure_lifo_push(app);
    app->program.label_target = value;
}

void cpu_procedure_back(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    VALIDATE_NOT_ADRESS
    app->program.curr = ds_procedure_lifo_pop(app);
    driver_mode_set(app, MODE_PROCEDURE);
}

void cpu_procedure_fcal(PARAMS_DEFINE)
{
    REQUIRED_VALUE
    VALIDATE_NOT_ADRESS
    if (AUX != 0) {
        ds_procedure_lifo_push(app);
        app->program.label_target = value;
    }
}

void cpu_procedure_zcal(PARAMS_DEFINE)
{
    REQUIRED_VALUE
    VALIDATE_NOT_ADRESS
    if (AUX == 0) {
        ds_procedure_lifo_push(app);
        app->program.label_target = value;
    }
}

void cpu_procedure_pcal(PARAMS_DEFINE)
{
    REQUIRED_VALUE
    VALIDATE_NOT_ADRESS
    if (AUX > 0) {
        ds_procedure_lifo_push(app);
        app->program.label_target = value;
    }
}

void cpu_procedure_ncal(PARAMS_DEFINE)
{
    REQUIRED_VALUE
    VALIDATE_NOT_ADRESS
    if (AUX < 0) {
        ds_procedure_lifo_push(app);
        app->program.label_target = value;
    }
}

void cpu_procedure_fret(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    VALIDATE_NOT_ADRESS
    if (AUX != 0) {
        app->program.curr = ds_procedure_lifo_pop(app);
        driver_mode_set(app, MODE_PROCEDURE);
    }
}

void cpu_procedure_zret(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    VALIDATE_NOT_ADRESS
    if (AUX == 0) {
        app->program.curr = ds_procedure_lifo_pop(app);
        driver_mode_set(app, MODE_PROCEDURE);
    }
}

void cpu_procedure_pret(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    VALIDATE_NOT_ADRESS
    if (AUX > 0) {
        app->program.curr = ds_procedure_lifo_pop(app);
        driver_mode_set(app, MODE_PROCEDURE);
    }
}

void cpu_procedure_nret(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    VALIDATE_NOT_ADRESS
    if (AUX < 0) {
        app->program.curr = ds_procedure_lifo_pop(app);
        driver_mode_set(app, MODE_PROCEDURE);
    }
}
