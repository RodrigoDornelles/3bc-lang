#ifndef _LANG_3BC_H
#define _LANG_3BC_H

/** prepare **/
#include "3bc_macros.h"

/** libaries **/
#if !defined(_3BC_MOS6502)
#include <math.h>
#endif
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>
#include <string.h>
#if defined(_3BC_COMPUTER)
#include <signal.h>
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

/** headers **/
#include "3bc_errors.h"
#include "3bc_types.h"
#include "3bc_header.h"
#include "3bc_register.h"
#if defined(_3BC_APP_UNIQUE)
#include "3bc_bootstrap.h"
#endif

/** program **/
#if !defined(_3BC_SCU)
#include "cpu_bool.c"
#include "cpu_common.c"
#include "cpu_debug.c"
#include "cpu_helper.c"
#include "cpu_input.c"
#include "cpu_math.c"
#include "cpu_jump.c"
#include "cpu_memory.c"
#include "cpu_procedure.c"
#include "cpu_string.c"
#include "driver_io.c"
#include "driver_gpio.c"
#include "driver_memory.c"
#include "driver_power.c"
#include "driver_program.c"
#include "ds_memory_llrbt.c"
#include "ds_procedure_lifo.c"
#include "interpreter_compiler.c"
#include "interpreter_parser.c"
#include "interpreter_syntax.c"
#include "interpreter_tokens.c"
#include "tape_aux.c"
#include "tape_program.c"
#include "tape_router.c"
#endif
#endif
