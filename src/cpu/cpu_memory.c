/**
 * @internal
 *  ___________  _____   _
 * |____ | ___ \/  __ \ | |
 *     / / |_/ /| /  \/ | | __ _ _ __   __ _ _   _  __ _  __ _  ___
 *     \ \ ___ \| |     | |/ _` | '_ \ / _` | | | |/ _` |/ _` |/ _ \
 * .___/ / |_/ /| \__/\ | | (_| | | | | (_| | |_| | (_| | (_| |  __/
 * \____/\____/  \____/ |_|\__,_|_| |_|\__, |\__,_|\__,_|\__, |\___|
 *                                     __/ |             __/ |
 *                                    |___/             |___/
 * @endinternal
 * @file cpu_memory.c
 *
 * @brief
 * Code refers registers for memory manipulation.
 *
 * @copyright
 * Low-level language, tiny virtual machine, intermediate representation,     \n
 * embeddable, easy for beginners. (Friendly Punched cards)                   \n
 *                                                                            \n
 * Copyright (C) 2020 Rodrigo Dornelles.                                      \n
 *                                                                            \n
 * This program is free software: you can redistribute it and/or modify       \n
 * it under the terms of the GNU General Public License as published by       \n
 * the Free Software Foundation, either version 3 of the License,             \n
 * or any later version.                                                      \n
 *                                                                            \n
 * This program is distributed in the hope that it will be useful,            \n
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             \n
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              \n
 * GNU General Public License for more details.                               \n
 *                                                                            \n
 * You should have received a copy of the GNU General Public License          \n
 * along with this program.  If not, see <https://www.gnu.org/licenses/>. 
 *
 */

#define TBC_SOURCE_ENTRY
#include "3bc.h"

/**
 * @brief clear memory
 */
void cpu_memory_free(struct app_3bc_s* const self)
{
    do {
        if (self->rc != TBC_RET_SYS_MEM_WRITE){
            self->rc = TBC_RET_SYS_MEM_WRITE;
            self->cpu.ra ^= self->cpu.ra;
            break;
        }

        self->rc = TBC_RET_OK;
    }
    while(0);
}

/**
 * @brief store in memory from constant
 */
void cpu_memory_aloc(struct app_3bc_s* const self)
{
    do {
        if (self->rc != TBC_RET_SYS_MEM_WRITE){
            self->rc = TBC_RET_SYS_MEM_WRITE;
            self->cpu.ra = self->cpu.rz;
            break;
        }

        self->rc = TBC_RET_OK;
    }
    while(0);
}

void cpu_memory_moff(PARAMS_DEFINE)
{
    /** @todo this config remove mask (and not)
    driver_memory_conf_set(
        app, address, driver_memory_conf_get(app, address) & ~value);
    */
}

void cpu_memory_muse(PARAMS_DEFINE)
{
    /** @todo this config append mask (or) 
    driver_memory_conf_set(
        app, address, driver_memory_conf_get(app, address) | value);
    */
}

void cpu_memory_ptr_free(PARAMS_DEFINE)
{
    /*
    driver_memory_free(app, POINTER(address));
    */
}

void cpu_memory_ptr_aloc(PARAMS_DEFINE)
{
    /*
    driver_memory_data_set(app, POINTER(address), value);
    */
}

/**
 * @startuml
 * rectangle pointer {
 *  rectangle mem
 * }
 * rectangle aux
 * aux -left-> mem
 * @enduml
 */
void cpu_memory_ptr_pull(PARAMS_DEFINE)
{
    /*
    driver_memory_data_set(app, POINTER(address), AUX);
    */
}

/**
 * @startuml
 * rectangle pointer {
 *  rectangle mem
 * }
 * rectangle aux
 * mem -right-> aux
 * @enduml
 */
void cpu_memory_ptr_push(PARAMS_DEFINE)
{
    /*
    driver_accumulator_set(app, driver_memory_data_get(app, POINTER(address)));
    */
}

/**
 * @startuml
 * rectangle pointer {
 *  rectangle mem
 * }
 * rectangle aux
 * mem -right-> aux
 * aux -left-> mem
 * @enduml
 */
void cpu_memory_ptr_spin(PARAMS_DEFINE)
{
    /**
    {
        data_3bc_t aux_old = AUX;
        address = POINTER(address);
        driver_accumulator_set(app, driver_memory_data_get(app, address));
        driver_memory_data_set(app, address, aux_old);
    }*/
}

/**
 * @brief clear accumulator
 */
void cpu_memory_aux_free(struct app_3bc_s* const self)
{
    self->cpu.ra ^= self->cpu.ra;
}

/**
 * @brief store in accumulator from constant.
 */
void cpu_memory_aux_aloc(struct app_3bc_s* const self)
{
    self->cpu.ra = self->cpu.rz;
}

/**
 * @brief store in memory from accumulator
 * @startuml
 * rectangle mem
 * rectangle aux
 * aux -left-> mem
 * @enduml
 */
void cpu_memory_aux_pull(struct app_3bc_s* const self)
{
    do {
        if (self->rc != TBC_RET_SYS_MEM_WRITE){
            self->rc = TBC_RET_SYS_MEM_WRITE;
            break;
        }

        self->rc = TBC_RET_OK;
    }
    while(0);
}

/**
 * @brief store in accumulator from memory
 * @startuml
 * rectangle mem
 * rectangle aux
 * mem -right-> aux
 * @enduml
 */
void cpu_memory_aux_push(struct app_3bc_s* const self)
{
    do {
        if (self->rc != TBC_RET_SYS_MEM_READ){
            self->rc = TBC_RET_SYS_MEM_READ;
            break;
        }

        self->rc = TBC_RET_OK;
    }
    while(0);
}

/**
 * @short invert values bettwen memory and accumulator
 * @startuml
 * rectangle mem
 * rectangle aux
 * mem -right-> aux
 * aux -left-> mem
 * @enduml
 */
void cpu_memory_aux_spin(struct app_3bc_s* const self)
{
    do {
        if (self->rc == TBC_RET_OK){
            self->cache_l2.i16[0] = self->cpu.ra;
            self->rc = TBC_RET_SYS_MEM_READ;
            break;
        }

        if (self->rc == TBC_RET_SYS_MEM_READ) {
            self->cache_l2.i16[1] = self->cpu.ra;
            self->cpu.ra = self->cache_l2.i16[0];
            self->rc = TBC_RET_SYS_MEM_WRITE;
            break;
        }

        if (self->rc == TBC_RET_SYS_MEM_WRITE) {
            self->cpu.ra = self->cache_l2.i16[1];
            self->rc = TBC_RET_GC_LV2;
            break;
        }

        self->rc = TBC_RET_OK;
    }
    while(0);
}