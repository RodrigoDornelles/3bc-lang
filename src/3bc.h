#ifndef _LANG_3BC_H
#define _LANG_3BC_H

/** libaries **/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <unistd.h>
#include <termios.h>

/** headers **/
#include "3bc_header.h"
#include "3bc_register.h"

/** program **/
#include "cpu_common.c"
#include "cpu_debug.c"
#include "cpu_input.c"
#include "cpu_jump.c"
#include "cpu_memory.c"
#include "cpu_string.c"
#include "lang_line.c"
#include "lang_driver.c"
#include "parser_interpreter.c"
#include "parser_transpiler.c"
#include "parser_compiler.c"
#include "tape_aux.c"
#include "tape_memory.c"
#include "tape_program.c"
#include "tape_router.c"

#endif