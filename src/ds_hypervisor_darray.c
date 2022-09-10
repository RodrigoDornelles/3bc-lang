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
static app_3bc_id machines_pool_size = 1;
static struct app_3bc_s** machines_array = NULL;

/**
 * Expand number of virtual machine
 */
struct app_3bc_s* const ds_hypervisor_darray_new()
{
    const size_t size_vm = sizeof(struct app_3bc_s);
    const size_t size_vmp = sizeof(struct app_3bc_s*);
    struct app_3bc_s** new_reseved = NULL;
    struct app_3bc_s** new_array = machines_array;
    struct app_3bc_s* new_vm = NULL;
    size_t bex = 0;

    fprintf(stderr, "\nHV");

    do {
        
#if !defined(TBC_BEX_ACTIVE)
        /** new instance **/
        new_vm = (struct app_3bc_s* const) malloc(size_vm);

        /** failed instance **/
        if(new_vm != NULL) {
            break;
        }
#endif

        /** calculate pool **/
        if (machines_pool_size <= (machines_count + 1)) {
            #if defined(TBC_BEX_LINEAR)
            machines_pool_size += 1u;
            #elif defined(TBC_BEX_B2)
            machines_pool_size <<= 1;
            #elif defined(TBC_BEX_B10)
            machines_pool_size *= 10;   
            #endif
    
            /** expand pool **/
            bex = (machines_pool_size + 1) * size_vmp;
            new_array = (struct app_3bc_s**) realloc(machines_array, bex);

#if defined(TBC_BEX_ACTIVE)
            /** instantiate reserve machines **/
            bex = machines_pool_size - machines_count;
            new_reseved = (struct app_3bc_s**) malloc(bex * size_vm);

            /** success allocate cluster of machines **/
            if(new_array != NULL && new_reseved != NULL) {
                /** mark usefull machine **/
                new_reseved[0]->leader = true;
                /** link reserve machines in the pool **/
                for (;bex < machines_pool_size; bex++) {
                    new_array[machines_count + bex] = new_reseved[bex];
                }
            }
#endif
        }

        /** failed pool **/
        if (new_array == NULL) {
            if (new_vm != NULL) {
                free(new_vm);
                new_vm = NULL;
            }
            break;
        }

        /** setup hypervisor **/
        machines_array = new_array;
        machines_array[machines_count] = new_vm;
        machines_array[machines_pool_size] = NULL;
        memset(new_vm, 0, sizeof(struct app_3bc_s));

        /** basic setup machine **/
        new_vm->id = machines_count++;
        new_vm->memory.data_get = &ds_memory_llrbt_data_get;
        new_vm->memory.conf_get = &ds_memory_llrbt_conf_get;
        new_vm->memory.data_set = &ds_memory_llrbt_data_set;
        new_vm->memory.conf_set = &ds_memory_llrbt_conf_set;
    }
    while(false);

    fprintf(stderr, "!");

    return new_vm;
}

/**
 * RETURN: virutal machine by id
 */
struct app_3bc_s* const ds_hypervisor_darray_get_one(app_3bc_id app)
{
    return machines_array[app];
}

/**
 *  RETURN: array of virtual machines
 */
struct app_3bc_s** ds_hypervisor_darray_get_all()
{
    return machines_array;
}

void ds_hypervisor_darray_kill_all()
{
    /** free each machine **/
    do {
        machines_count -= 1;
#if defined(TBC_BEX_ACTIVE)
        if (machines_array[machines_count]->leader) {
            free(machines_array[machines_count]);
        }
#else
        free(machines_array[machines_count]);
#endif       
    } while (machines_count);

    /** reset hypervisor **/
    free(machines_array);
    machines_array = NULL;
}