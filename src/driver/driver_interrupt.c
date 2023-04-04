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
 * @file driver_interrupt.c
 *
 * @brief
 * Code refers to the managing contexts and interrupt's of the virtual machine.
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
 * @par Joke
 * @code{.unparsed}
 * _\|/_ weedend alert! _\|/_
 * this code was written in a 4:20 mode.
 * @endcode
 */

#define TBC_SOURCE_ENTRY
#include "3bc.h"
#include "driver_cpu.h"
#include "driver_gc.h"
#include "bus_cpu_0000.h"
#include "bus_sys_0000.h"

/**
 * VM processor context manager, allows asychronism.
 *
 * @startuml
 * [*] --> FSM_3BC_DEFAULT
 * FSM_3BC_DEFAULT --> FSM_3BC_STARTING
 * FSM_3BC_STARTING --> FSM_3BC_VACUUM
 * FSM_3BC_VACUUM --> FSM_3BC_INTERPRETER
 * FSM_3BC_RUNNING --> FSM_3BC_ERROR
 * FSM_3BC_RUNNING --> FSM_3BC_RUNNING
 * FSM_3BC_RUNNING --> FSM_3BC_SYSCALL
 * FSM_3BC_RUNNING --> FSM_3BC_COUNTING
 * FSM_3BC_SYSCALL --> FSM_3BC_SYSCALL
 * FSM_3BC_SYSCALL --> FSM_3BC_RUNNING
 * FSM_3BC_SYSCALL --> FSM_3BC_ERROR
 * FSM_3BC_INTERPRETER --> FSM_3BC_INTERPRETER
 * FSM_3BC_INTERPRETER --> FSM_3BC_LOADING
 * FSM_3BC_INTERPRETER --> FSM_3BC_EXITING
 * FSM_3BC_INTERPRETER --> FSM_3BC_ERROR
 * FSM_3BC_SYSCALL --> FSM_3BC_EXITING
 * FSM_3BC_LOADING --> FSM_3BC_RUNNING
 * FSM_3BC_COUNTING --> FSM_3BC_VACUUM
 * FSM_3BC_ERROR --> FSM_3BC_EXITING
 * FSM_3BC_EXITING --> FSM_3BC_STOPED
 * FSM_3BC_STOPED --> [*]
 * @enduml
 */
bool driver_interrupt(struct app_3bc_s* const self)
{
    /*
     * HARD INTERRUPTS
     */
    if (self->rc < 0) {
        if (self->rc == TBC_RET_EXIT) {
            self->state = FSM_3BC_EXITING;
        }
        else if (self->rc == TBC_RET_EXIT_FORCE) {
            self->state = FSM_3BC_STOPED;
        }
        /** NOTE: garbage collector routine has negatives values **/
        else if (TBC_RET_GC_LV1 >= self->rc && self->rc >= TBC_RET_GC_LV4) {
            driver_gc(self);
            /** @todo change to break */
            return true;
        }
    }

    switch (self->state) {
    case FSM_3BC_DEFAULT:
        self->state = FSM_3BC_STARTING;
        return true;

    case FSM_3BC_STARTING:
        self->pkg_func = (tbc_pkg_st*) &tbc_pkg_standard;
        self->state = FSM_3BC_RUNNING;
        return true;

    case FSM_3BC_EXPAND:
        self->pkg_func->prog.expand(self);
        if(self->rc == TBC_RET_OK) {
            self->state = FSM_3BC_READING;
        }
        return true;

    case FSM_3BC_READING:
        interpreter_ticket(self);
        if (self->rc == TBC_RET_OK) {
            self->state = FSM_3BC_RUNNING;
        }
        return true;

    case FSM_3BC_RUNNING:
        /** 
         * @note cache level 0 is re-used in evaluate.
         */
        self->pkg_func->prog.avaliable(self);
        if (self->rc == TBC_RET_CLEAN) {
            self->state = FSM_3BC_EXPAND;
            return true;
        }

        /* evaluate */
        self->pkg_func->prog.load(self);
        driver_cpu(self);
        self->hyperload(self);

        /* soft interrupt **/
        if (self->rc == TBC_RET_SYSCALL) {
            self->previous = self->state;
            self->state = FSM_3BC_SYSCALL;
            return true;
        }
        /* program counting **/
        else {
            self->state = FSM_3BC_COUNTING;
        }
        return true;

    case FSM_3BC_COUNTING:
        self->pkg_func->prog.next(self);
        self->state = FSM_3BC_RUNNING;
        return true;

    case FSM_3BC_SYSCALL:
        switch(self->cache_l1.syscall) {
           case TBC_SYS_MEM_READ:
            self->state = FSM_3BC_MEM_READ;
            break;

            case TBC_SYS_MEM_WRITE:
            self->state = FSM_3BC_MEM_WRITE;
            break;

            case TBC_SYS_IO_WRITE:
            self->state = FSM_3BC_IO_WRITE;
            break;

            case TBC_SYS_WAIT:
            self->state = FSM_3BC_WAITING;
            break;
        }
        return true;

    case FSM_3BC_WAITING:
        if (!driver_idle(self)) {
            self->state = FSM_3BC_RUNNING;
            self->cache_l1.sleep_mode = SLEEP_3BC_NONE;
            self->cache_l2.sleep_period = 0;
            self->cache_l3.sleep_called = 0;
        }
        return true;

    /**
     * @todo
    case FSM_3BC_IO_READ:
        self->state = FSM_3BC_RUNNING;
        return true;*/

    case FSM_3BC_IO_WRITE:
        self->pkg_func->io.write(self);
        self->state = self->previous;
        return true;

    case FSM_3BC_MEM_READ:
        self->pkg_func->ram.read(self);
        self->state = self->previous;
        return true;

    case FSM_3BC_MEM_WRITE:
        self->pkg_func->ram.write(self);
        self->state = self->previous;
        return true;

    case FSM_3BC_EXITING:
        driver_power_exit(self);
        /** @todo investigate why not set **/
        self->state = FSM_3BC_STOPED;
        return false;
    }

    return false;
}