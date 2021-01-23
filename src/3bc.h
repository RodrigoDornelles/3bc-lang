#ifndef _LANG_3BC_H
#define _LANG_3BC_H

/** prepare **/
#include "3bc_macros.h"

/** libaries **/
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#ifdef _3BC_COMPUTER
#include <signal.h>
#endif
#ifdef _3BC_PC_NOT_WINDOWS
#include <termios.h>
#endif

/** headers **/
#include "3bc_errors.h"
#include "3bc_header.h"
#include "3bc_register.h"

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
#include "lang_line.c"
#include "lang_driver.c"
#include "lang_interpreter.c"
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