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
 * Code refers to the managing contexts and interrupt's of the virtual machine.
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
 *
 * JOKE:
 * _\|/_ weedend alert! _\|/_
 * this code was written in a 4:20 mode.
 */

#define TBC_SOURCE_ENTRY
#include "3bc.h"
#include "driver_gc.h"
#include "pkg_std_0000.h"

/**
 * VM processor context manager, allows asychronism.
 */
bool driver_interrupt(struct app_3bc_s* const self)
{
    /**
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
            /** TODO: change to break */
            return true;
        }
    }

    switch (self->state) {
    /**
     * INITIAL CONTEXT
     */
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

    /**
     *  INTERPRETER CONTEXT
     */
    case FSM_3BC_READING:
        interpreter_ticket(self);
        if (self->rc == TBC_RET_OK) {
            self->state = FSM_3BC_RUNNING;
        }
        return true;

    /**
     * PROCESS CONTEXT
     */
    case FSM_3BC_RUNNING:
        /** 
         * check for program existence
         * @note cache level 0 is re-used in evaluate.
         */
        self->pkg_func->prog.avaliable(self);
        if (self->rc == TBC_RET_CLEAN) {
            self->state = FSM_3BC_EXPAND;
            return true;
        }

        /** evaluate */
        self->pkg_func->prog.load(self);
        instruction_3bc(self);

        /** soft interrupt **/
        if (self->rc == TBC_RET_SYSCALL) {
            self->previous = self->state;
            self->state = FSM_3BC_SYSCALL;
            return true;
        }
        /** program counting **/
        else {
            self->state = FSM_3BC_COUNTING;
        }
        return true;

    case FSM_3BC_COUNTING:
        self->pkg_func->prog.next(self);
        self->state = FSM_3BC_RUNNING;
        return true;

    case FSM_3BC_SYSCALL:
        /** @brief virtual machine interrupt: write */
        if (self->cpu_mode == TBC_MODE_STRING && self->cache_l1.printing) {
            self->state = FSM_3BC_IO_SEND;
        }
        /** @brief virtual machine interrupt: idle */
        else if (self->cpu_mode == TBC_MODE_SLEEP
            && self->cache_l1.sleep_mode != SLEEP_3BC_NONE) {
            self->state = FSM_3BC_WAITING;
        }
        return true;

    /**
     * SLEEP CONTEXT
     */
    case FSM_3BC_WAITING:
        if (!driver_idle(self)) {
            self->state = FSM_3BC_RUNNING;
            self->cache_l1.sleep_mode = SLEEP_3BC_NONE;
            self->cache_l2.sleep_period = 0;
            self->cache_l3.sleep_called = 0;
        }
        return true;

    /**
     * INPUT CONTEXT
     * TODO: this
    case FSM_3BC_IO_READ:
        self->state = FSM_3BC_RUNNING;
        return true;*/

    /**
     * @brief OUTPUT CONTEXT
     */
    case FSM_3BC_IO_SEND:
        self->pkg_func->io.write(self);
        self->state = self->previous;
        return true;

    /**
     * EXIT CONTEXT
     */
    case FSM_3BC_EXITING:
        driver_power_exit(self);
        /** @todo investigate why not set*/
        self->state = FSM_3BC_STOPED;
        return false;
    }

    return false;
}