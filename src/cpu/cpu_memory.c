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
 * Code refers registers for memory manipulation.
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

void cpu_memory_free(PARAMS_DEFINE)
{
    REQUIRED_ADDRESS
    VALIDATE_NOT_VALUES
    if (!app->cache_l1.syscall) {
        app->rc = TBC_RET_SYSCALL;
        app->cache_l1.syscall = TBC_SYS_MEM_WRITE;
        app->mem_aux ^= app->mem_aux;
    }
    else {
        app->rc = TBC_RET_GC_LV1;
    }
}

void cpu_memory_aloc(PARAMS_DEFINE)
{
    REQUIRED_ADDRESS
    if (!app->cache_l1.syscall) {
        app->rc = TBC_RET_SYSCALL;
        app->cache_l1.syscall = TBC_SYS_MEM_WRITE;
        app->mem_aux = app->cache_l0.rz;
    }
    else {
        app->rc = TBC_RET_GC_LV1;
    }
}

void cpu_memory_moff(PARAMS_DEFINE)
{
    REQUIRED_ADDRESS
    /** config remove mask (and not) */
    driver_memory_conf_set(
        app, address, driver_memory_conf_get(app, address) & ~value);
}

void cpu_memory_muse(PARAMS_DEFINE)
{
    REQUIRED_ADDRESS
    /** config append mask (or) */
    driver_memory_conf_set(
        app, address, driver_memory_conf_get(app, address) | value);
}

void cpu_memory_ptr_free(PARAMS_DEFINE)
{
    REQUIRED_ADDRESS
    VALIDATE_NOT_VALUES
    driver_memory_free(app, POINTER(address));
}

void cpu_memory_ptr_aloc(PARAMS_DEFINE)
{
    REQUIRED_ADDRESS
    driver_memory_data_set(app, POINTER(address), value);
}

void cpu_memory_ptr_pull(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    driver_memory_data_set(app, POINTER(address), AUX);
}

void cpu_memory_ptr_push(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    driver_accumulator_set(app, driver_memory_data_get(app, POINTER(address)));
}

void cpu_memory_ptr_spin(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    {
        data_3bc_t aux_old = AUX;
        address = POINTER(address);
        driver_accumulator_set(app, driver_memory_data_get(app, address));
        driver_memory_data_set(app, address, aux_old);
    }
}

void cpu_memory_aux_free(PARAMS_DEFINE)
{
    VALIDATE_NOT_ADRESS
    VALIDATE_NOT_VALUES
    app->mem_aux ^= app->mem_aux;
}

void cpu_memory_aux_aloc(PARAMS_DEFINE)
{
    VALIDATE_NOT_ADRESS
    app->mem_aux = app->cache_l0.rz;
}

void cpu_memory_aux_pull(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    if (!app->cache_l1.syscall) {
        app->rc = TBC_RET_SYSCALL;
        app->cache_l1.syscall = TBC_SYS_MEM_READ;
    }
    else {
        app->rc = TBC_RET_GC_LV1;
    }
}

void cpu_memory_aux_push(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    if (!app->cache_l1.syscall) {
        app->rc = TBC_RET_SYSCALL;
        app->cache_l1.syscall = TBC_SYS_MEM_WRITE;
    }
    else {
        app->rc = TBC_RET_GC_LV1;
    }
}

/**
 * invert values inner AUX & Memory
 */
void cpu_memory_aux_spin(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    /** TODO: this
    {
        data_3bc_t aux_old = AUX;
        driver_accumulator_set(app, driver_memory_data_get(app, address));
        driver_memory_data_set(app, address, aux_old);
    }*/
}