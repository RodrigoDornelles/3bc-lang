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
 * Code refers to the virtual machine's launcher.
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

static app_3bc_id machines_count;
static struct app_3bc_s** machines_array;

/**
 * Expand number of virtual machines
 */
struct app_3bc_s* const ds_hypervisor_darray_new()
{
    struct app_3bc_s* new_vm
        = (struct app_3bc_s* const)malloc(sizeof(struct app_3bc_s));

    /** successful craete new machine **/
    if (new_vm != NULL) {
        /** expand hypervisor **/
        struct app_3bc_s** new_array = (struct app_3bc_s**) realloc(
            machines_array, (sizeof(struct app_3bc_s*) * (machines_count + 2)));

        /** not possible expand array **/
        if (new_array == NULL) {
            free(new_vm);
            return NULL;
        }

        /** setup hypervisor **/
        machines_array = new_array;
        machines_array[machines_count] = new_vm;
        machines_array[machines_count + 1] = NULL;
        memset(new_vm, 0, sizeof(struct app_3bc_s));

        /** basic setup machine **/
        new_vm->id = machines_count++;
        new_vm->memory.data_get = &ds_memory_llrbt_data_get;
        new_vm->memory.conf_get = &ds_memory_llrbt_conf_get;
        new_vm->memory.data_set = &ds_memory_llrbt_data_set;
        new_vm->memory.conf_set = &ds_memory_llrbt_conf_set;

        return new_vm;
    }

    return NULL;
}

/**
 * RETURN: virutal machine by id
 */
struct app_3bc_s* const ds_hypervisor_darray_get_one(app_3bc_id app)
{
    return machines_array[app - 1];
}

/**
 *  RETURN: array of virtual machines
 */
struct app_3bc_s** ds_hypervisor_darray_get_all()
{
    return machines_array;
}
