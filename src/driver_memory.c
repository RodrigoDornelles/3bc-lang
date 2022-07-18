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
 * Code refers main memory access.
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

void driver_memory_data_set(
    struct app_3bc_s* const app, address_3bc_t address, data_3bc_t value)
{
    memory_conf_t conf = app->memory.conf_get(app->id, address);

    driver_gpio_output(app, conf, address, value);

    app->memory.data_set(app->id, address, value);
}

void driver_memory_conf_set(
    struct app_3bc_s* const app, address_3bc_t address, data_3bc_t conf)
{
    data_3bc_t value = app->memory.data_get(app->id, address);

    driver_memory_validate(app, conf);
    driver_gpio_setup(app, conf, address);
    driver_gpio_output(app, conf, address, value);
    value = driver_gpio_input(app, conf, address, value);

    app->memory.conf_set(app->id, address, conf);
    app->memory.data_set(app->id, address, value);
}

data_3bc_t driver_memory_data_get(
    struct app_3bc_s* const app, address_3bc_t address)
{
    data_3bc_t value = app->memory.data_get(app->id, address);
    memory_conf_t conf = app->memory.conf_get(app->id, address);

    /** read gpios if necessary **/
    value = driver_gpio_input(app, conf, address, value);

    return value;
}

data_3bc_t driver_memory_conf_get(
    struct app_3bc_s* const app, address_3bc_t address)
{
    return app->memory.conf_get(app->id, address);
}

/**
 * MACRO: POINTER
 */
address_3bc_t driver_memory_pointer(
    struct app_3bc_s* const app, address_3bc_t address)
{
    data_3bc_t ptr = driver_memory_data_get(app, address);

    /**
     * JOKE:
     *
     * JAVA PROGRAMMER BE LIKE
     * omg i'm scared with null pointer!
     */
    if (ptr == NILL) {
        /** also apply to microsoft java devs (aka C#) */
        driver_program_error(app, ERROR_NULL_POINTER);
    } else if (ptr < 0) {
        driver_program_error(app, ERROR_NUMBER_NEGATIVE);
    }

    return (address_3bc_t)ptr;
}

void driver_memory_validate(struct app_3bc_s* const app, memory_conf_t conf)
{
    /** optimize **/
    if (conf == 0) {
        return;
    }
    /** not allow pullup and analogic some times **/
    if (BITFIELD_HAS(conf, MEM_CONFIG_GPIO_ANAL | MEM_CONFIG_GPIO_PULL)) {
        driver_program_error(app, ERROR_MEMORY_CONFIG);
    }
    /** not allow pullup and output some times **/
    if (BITFIELD_HAS(conf, MEM_CONFIG_GPIO_SEND | MEM_CONFIG_GPIO_PULL)) {
        driver_program_error(app, ERROR_MEMORY_CONFIG);
    }
    /** not allow input and output some times **/
    if (BITFIELD_HAS(conf, MEM_CONFIG_GPIO_SEND | MEM_CONFIG_GPIO_READ)) {
        driver_program_error(app, ERROR_MEMORY_CONFIG);
    }
    /** analogic required input or output **/
    if (BITFIELD_HAS(conf, MEM_CONFIG_GPIO_ANAL)
        && !(BITFIELD_HAS(conf, MEM_CONFIG_GPIO_READ)
            || BITFIELD_HAS(conf, MEM_CONFIG_GPIO_SEND))) {
        driver_program_error(app, ERROR_MEMORY_CONFIG);
    }
}

void driver_memory_free(struct app_3bc_s* const app, address_3bc_t address)
{
    /** clear cache level 0 **/
    if (app->memory.cache != NULL && app->memory.cache->address == address) {
        app->memory.cache = NULL;
    }

    /** clear memory node **/
    /** TODO: move to ds_memory_llrbt **/
    app->memory.root = ds_memory_llrbt_clear(address, app->memory.root);
}