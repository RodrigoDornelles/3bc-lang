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
 * Library entry point.
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

#ifndef _LANG_3BC_H
#define _LANG_3BC_H

/** library info **/
#define VERSION_3BC "0.1.4"
#define VERSION_3BC_MAJOR 0
#define VERSION_3BC_MINOR 1
#define VERSION_3BC_PATCH 4

/** environment check **/
#include "3bc_detect.h"

/** prepare **/
#include "3bc_macros.h"

/**
 *   ___  ______ _____
 *  / _ \ | ___ \_   _|
 * / /_\ \| |_/ / | |
 * |  _  || ___ \ | |
 * | | | || |_/ /_| |_
 * \_| |_/\____/ \___/
 *
 * BRIEF: The Application binary interface helps
 * to integrate virtual machine drivers with host system modules.
 */
#if !defined(TBC_NOT_MATH)
#include <math.h>
#endif
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#if defined(TBC_P_COMPUTER)
#include <signal.h>
#include <time.h>
#endif
#if defined(TBC_USE_POSIX)
#include <termios.h>
#endif
#if defined(TBC_USE_CONIO)
#include <conio.h>
#endif
#if defined(TBC_USE_ARDUINO)
#include <Arduino.h>
#endif
#if defined(TBC_KERNEL_NUTTX)
#include <nuttx/config.h>
#endif

/** TODO: move to supporting file **/
#ifndef SIGTERM
#define SIGTERM (15)
#endif

/**
 *  _   _                _
 * | | | |              | |
 * | |_| | ___  __ _  __| | ___ _ __ ___
 * |  _  |/ _ \/ _` |/ _` |/ _ \ '__/ __|
 * | | | |  __/ (_| | (_| |  __/ |  \__ \
 * \_| |_/\___|\__,_|\__,_|\___|_|  |___/
 */

/** consts and types **/
#include "3bc_errors.h"
#include "3bc_types.h"

/** functions prototypes **/
#include "3bc_header.h"

/* opcodes and witchcraft **/
#include "3bc_register.h"

/**
 *  _____                            _____           _
 * /  ___|                          /  __ \         | |
 * \ `--.  ___  _   _ _ __ ___ ___  | /  \/ ___   __| | ___
 *  `--. \/ _ \| | | | '__/ __/ _ \ | |    / _ \ / _` |/ _ \
 * /\__/ / (_) | |_| | | | (_|  __/ | \__/\ (_) | (_| |  __/
 * \____/ \___/ \__,_|_|  \___\___|  \____/\___/ \__,_|\___|
 */

/** default source **/
#if !defined(TBC_SCU)
#include "cpu_boolean.c"
#include "cpu_common.c"
#include "cpu_jump.c"
#include "cpu_math.c"
#include "cpu_memory.c"
#include "cpu_procedure.c"
#include "cpu_sleep.c"
#include "cpu_string.c"
#include "driver_accumulator.c"
#include "driver_custom.c"
#include "driver_gpio.c"
#include "driver_idle.c"
#include "driver_interrupt.c"
#include "driver_memory.c"
#include "driver_mode.c"
#include "driver_power.c"
#include "driver_program.c"
#include "driver_tty.c"
#include "ds_hypervisor_darray.c"
#include "ds_label_hash.c"
#include "ds_memory_llrbt.c"
#include "ds_procedure_lifo.c"
#include "ds_program_fifo.c"
#include "interpreter_parser.c"
#include "interpreter_readln.c"
#include "interpreter_syntax.c"
#include "interpreter_ticket.c"
#include "interpreter_tokens.c"
#endif
/** customizable source **/
#if defined(TBC_SCU_FORCE)
#include "driver_custom.c"
#include "interpreter_ticket.c"
#endif

#endif
