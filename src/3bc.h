#ifndef _LANG_3BC_H
#define _LANG_3BC_H

/** library info **/
#define VERSION_3BC "0.1.1"
#define VERSION_3BC_MAJOR 0
#define VERSION_3BC_MINOR 1
#define VERSION_3BC_PATCH 1

/** prepare **/
#include "3bc_macros.h"

/** libaries **/
#if !defined(_3BC_MOS6502)
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
#if defined(_3BC_COMPUTER)
#include <signal.h>
#include <time.h>
#endif
#if defined(_3BC_PC_UNIX)
#include <termios.h>
#endif
#if defined(_3BC_PC_WINDOWS) || defined(_3BC_PC_1970)
#include <conio.h>
#endif
#if defined(_3BC_ARDUINO)
#include <Arduino.h>
#endif
#if defined(_3BC_NUTTX)
#include <nuttx/config.h>
#endif

/** consts and types **/
#include "3bc_errors.h"
#include "3bc_types.h"

/** functions prototypes **/
#include "3bc_header.h"

/* opcodes and witchcraft **/
#include "3bc_register.h"

/* some forbidden secret gimmicks **/
#include "3bc_optional_custom.h"
#include "3bc_optional_interpreter.h"

/** compatibility fixes **/
#include "3bc_support.h"

/** program code **/
#if !defined(_3BC_SCU)
#include "cpu_boolean.c"
#include "cpu_common.c"
#include "cpu_jump.c"
#include "cpu_math.c"
#include "cpu_memory.c"
#include "cpu_procedure.c"
#include "cpu_sleep.c"
#include "cpu_string.c"
#include "driver_accumulator.c"
#include "driver_gpio.c"
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
#endif
#endif
