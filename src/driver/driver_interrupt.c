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
#include "3bc_types.h"
#include "bus/bus_alu_0000.h"
#include "bus/bus_cpu_0000.h"
#include "bus/bus_sys_0000.h"
#include "driver/driver_error.h"
#include "driver/driver_cpu.h"
#include "driver/driver_gc.h"
#include "driver/driver_stack.h"

/**
 * @brief VM processor context manager, allows asychronism.
 * @return exit code
 * @retval -1 continue process.
 * @retval 0 process ended, it was a success.
 * @retval 1 process ended, an error occurred.
 *
 * @brief
 * all the functioning of the virtual machine runtime
 * including context manager, state machine, errors,
 * connection between guest drivers and host drivers,
 * and hardware and software interrupts is being handled
 * by this function.
 *
 * @note
 * **guest drivers** is a @ref src/driver source files.                      \n
 * **host drivers** is a @ref src/sys source files.                          \n
 *
 * @par Finite State Machine
 * @startuml fsm
 * [*] --> TBC_STATE_DEFAULT
 * TBC_STATE_DEFAULT -right-> TBC_STATE_STARTING
 * TBC_STATE_STARTING -right-> TBC_STATE_VACUUM
 * TBC_STATE_STARTING -[dotted]-> TBC_STATE_ERROR
 * TBC_STATE_VACUUM --> TBC_STATE_LOADING
 * TBC_STATE_VACUUM -[dotted]-> TBC_STATE_ERROR
 * TBC_STATE_RUNNING -[dotted]-> TBC_STATE_ERROR
 * TBC_STATE_RUNNING -right-> TBC_STATE_COUNTING
 * TBC_STATE_RUNNING --> TBC_STATE_VACUUM
 * TBC_STATE_RUNNING --> TBC_STATE_EXITING
 * TBC_STATE_LOADING -right-> TBC_STATE_RUNNING
 * TBC_STATE_LOADING -[dotted]-> TBC_STATE_ERROR
 * TBC_STATE_LOADING --> TBC_STATE_EXITING
 * TBC_STATE_COUNTING --> TBC_STATE_VACUUM
 * TBC_STATE_ERROR -right-> TBC_STATE_EXITING
 * TBC_STATE_EXITING -right-> TBC_STATE_STOPED
 * TBC_STATE_STOPED --> [*]
 * 
 * state TBC_STATE_VACUUM:<b>Interpreter FSM</b> <i>(optional)</i>
 * state TBC_STATE_RUNNING:<b>CPU FSM</b> <i>(optional)</i>
 * @enduml
 */
int driver_interrupt(struct app_3bc_s* const self)
{
    int exit_code = -1;

    do {
        /**
         * @par mask @c 0x80 in @c self->rc
         * @brief return code special cases.
         * @c 0b10000000
         * @li bit 7 must process something. (interrupt)
         */
        if (self->rc & 0x80) {
            switch ((tbc_u8_t) self->rc)
            {
                case TBC_RET_THROW_ERROR:
                    self->rc = TBC_RET_CATCH_ERROR;
                    self->state = FSM_3BC_ERROR;
                    break;

                case TBC_RET_EXIT_SAFE:
                    self->state = FSM_3BC_EXITING;
                    break;

                case TBC_RET_EXIT_FORCE:
                    self->state = FSM_3BC_STOPED;
                    break;

                case TBC_RET_SYS_MATH:
                    tbc_layout_alu(self);
                    break;

                case TBC_RET_SYS_MEM_READ:
                    self->pkg_func->ram.read(self);
                    break;

                case TBC_RET_SYS_MEM_WRITE:
                    self->pkg_func->ram.write(self);
                    break;

                case TBC_RET_SYS_IO_READ:
                    /** @todo self->pkg_func->io.read(self); **/
                    break;

                case TBC_RET_SYS_IO_WRITE:
                case TBC_RET_PRINT_ERROR_1:
                case TBC_RET_PRINT_ERROR_2:
                case TBC_RET_PRINT_ERROR_3:
                case TBC_RET_PRINT_ERROR_4:
                case TBC_RET_PRINT_ERROR_5:
                case TBC_RET_PRINT_ERROR_6:
                case TBC_RET_PRINT_ERROR_7:
                case TBC_RET_PRINT_ERROR_8:
                case TBC_RET_PRINT_ERROR_9:
                case TBC_RET_PRINT_ERROR_A:
                    if (self->pkg_func != NULL) {
                        self->pkg_func->io.write(self);
                    } else {
                        tbc_pkg_standard.io.write(self);
                    }
                    break;

                case TBC_RET_GC_LV1:
                case TBC_RET_GC_LV2:
                case TBC_RET_GC_LV3:
                case TBC_RET_GC_LV4:
                    driver_gc(self);
                    break;
            }
            /**
             * @par mask @c 0x40 in @c self->rc
             * @brief end processing cycle.
             * @c 0b01000000
             * @li bit 6 hard interrupts. (not execute machine state)
             * @li bit 7 is pre-condition nested branch.
             */
            if (self->rc & 0x40) {
                break;
            }
        }

        switch (self->state) {
        case FSM_3BC_DEFAULT:
            self->state = FSM_3BC_STARTING;
            break;

        case FSM_3BC_STARTING:
            /* host drivers */
            self->pkg_func = (tbc_pkg_st*) &tbc_pkg_standard;
            /* start minimal stack */
            if (self->stack.raw.buffer == NULL) {
                driver_stack_init(self, NULL, 0);
            }
            /* first state */
            if (self->rc == TBC_RET_OK) {
                self->state = FSM_3BC_VACUUM;
            }
            break;

        case FSM_3BC_VACUUM:
            self->pkg_func->prog.avaliable(self);
            if (self->rc == TBC_RET_CLEAN) {
                self->state = FSM_3BC_EXPAND;
                break;
            }
            self->state = FSM_3BC_LOADING;
            break;

        case FSM_3BC_EXPAND:
            self->pkg_func->prog.expand(self);
            if(self->rc == TBC_RET_OK) {
                self->state = FSM_3BC_READING;
                self->rc = TBC_RET_CLEAN;
            }
            break;

        case FSM_3BC_READING:
            if (self->rc == TBC_RET_FULL) {
                self->pkg_func->prog.insert(self);
                self->state = FSM_3BC_LOADING;
            }
            if (self->rc == TBC_RET_CLEAN) {
                self->rc = TBC_RET_THROW_ERROR;
                self->cache_l1.error = ERROR_NOTHING_TO_DO;
            }
            break;

        case FSM_3BC_LOADING:
            self->pkg_func->prog.load(self);
            self->rc = TBC_RET_OK;
            driver_cpu(self);
            if (self->rc == TBC_RET_OK) {
                self->state = FSM_3BC_RUNNING;
            }
            break;

        case FSM_3BC_RUNNING:
            if (self->hyperload != NULL) {
                self->hyperload(self);
            }
            if (self->rc == TBC_RET_OK) {
                self->state = FSM_3BC_COUNTING;
            }
            if(self->rc == TBC_RET_RELOAD) {
                self->state = FSM_3BC_LOADING;
            }
            break;

        case FSM_3BC_ERROR:
            driver_error(self);
            if (self->rc == TBC_RET_OK) {
                self->state = FSM_3BC_EXITING;
                /** @todo work this **/
                exit_code = -1;
            }
            break;

        case FSM_3BC_COUNTING:
            self->pkg_func->prog.next(self);
            self->state = FSM_3BC_VACUUM;
            break;
        
        case FSM_3BC_EXITING:
            self->state = FSM_3BC_STOPED;
            break;
        
        case FSM_3BC_STOPED:
            exit_code = 0;
#if defined(TBC_FREEZE_STOPPED)
            while(1);
#endif
            break;
        }
    }
    while(0);

    return exit_code;
}