#ifndef _LANG_3BC_H
#define _LANG_3BC_H

/** prepare **/
#include "3bc_macros.h"

/** libaries **/
#include <math.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>
#include <string.h>
#ifdef _3BC_COMPUTER
#include <signal.h>
#endif
#ifdef _3BC_PC_NOT_WINDOWS
#include <termios.h>
#endif
#ifdef _3BC_PC_WINDOWS
#include <conio.h>
#endif

/** headers **/
#include "3bc_errors.h"
#include "3bc_types.h"
#include "3bc_header.h"
#include "3bc_register.h"
#ifdef _3BC_APP_UNIQUE
#include "3bc_bootstrap.h"
#endif

/** program **/
#ifdef _3BC_COMPUTER
#include "cpu_common.c"
#include "cpu_debug.c"
#include "cpu_helper.c"
#include "cpu_input.c"
#include "cpu_math.c"
#include "cpu_jump.c"
#include "cpu_memory.c"
#include "cpu_string.c"
#include "driver_io.c"
#include "driver_memory.c"
#include "driver_power.c"
#include "driver_program.c"
#include "interpreter_compiler.c"
#include "interpreter_parser.c"
#include "interpreter_sintax.c"
#include "tape_aux.c"
#include "tape_memory.c"
#include "tape_program.c"
#include "tape_router.c"
#include "tape_sort.c"
#ifdef __cplusplus
/** 
 * when require C++ adpatations
 */
#include "lang_plus.cpp"
#endif
#endif
#endif
