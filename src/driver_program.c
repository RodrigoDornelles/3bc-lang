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
 * Code refers to the counter program executor and error handler.
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

#define TBC_SOURCE_ENTRY
#define TBC_SOURCE_REGISTERS
#include "3bc.h"


/**
 * header used before error description.
 *
 * TODO:
 * more readable and move to 3bc_errors.h
 *
 * NOTE:
 * the size of the ID depends on the architecture.
 *
 * NOTE:
 * there is _3BC_COMPACT which makes information simpler (takes up less space). 
 *
 */
#if defined(TBC_OPT_COMPACT)
static const char error_header[] = "\n\n[3BC] %3d Fatal error 0x%06X in line: %06u\n";
#else
static const char error_header[] = 
    "\n[3BC] CRITICAL ERROR ABORTED THE PROGRAM\n> MACHINE ID:\t"
#if defined(TBC_ID_64_BITS) || defined(TBC_ID_32_BITS)
    "%08lu"
#elif defined(TBC_ID_16_BITS) || defined(TBC_ID_8_BITS)
    "%08u"
#endif
    "\n> ERROR LINE:\t%08u\n> ERROR CODE:\t0x%06X\n> DESCRIPTION: ";
#endif

/** 11 is padding of zeros missing **/
static const tbc_u8_t error_header_size = sizeof(error_header) + 11;

void driver_program_error(
    struct app_3bc_s* const app, enum error_3bc_e error_code)
{
    /**
     * NOTE: if the current line does not exist,
     * it was because it was interpreting a line which failed.
     *
     * TODO:
     * safer and remove ternaries.
     */
    line_3bc_t error_line
        = app->program.curr != NULL && error_code >= ERROR_CPU_ZERO
        ? app->program.curr->line
        : app->program.last_line;

    /** print header of error**/
    char error_code_string[error_header_size];
    snprintf(error_code_string, error_header_size, error_header, app->id, error_line, error_code);
    driver_tty_output_raw(app, app->tty_error, error_code_string);

    /** TODO: not use macros and move to 3bc_errors.h **/
#if !defined(TBC_OPT_COMPACT)
    switch ((long)(error_code)) {
#if defined(SIGSEGV)
        ERROR_LOG_3BC(SIGSEGV, "SEGMENT FAULT");
#endif
        ERROR_LOG_3BC(ERROR_CPU_ZERO, "CPU MODE IS NOT DEFINED");
        ERROR_LOG_3BC(ERROR_CPU_RESERVED, "CPU MODE IS RESERVED");
        ERROR_LOG_3BC(ERROR_INVALID_REGISTER, "INVALID CPU REGISTER");
        ERROR_LOG_3BC(ERROR_INVALID_ADDRESS, "INVALID ADDRESS");
        ERROR_LOG_3BC(ERROR_INVALID_CONSTANT, "INVALID CONSTANT");
        ERROR_LOG_3BC(ERROR_INVALID_CPU_MODE, "INVALID CPU MODE");
        ERROR_LOG_3BC(ERROR_INVALID_LABEL, "INVALID LABEL");
        ERROR_LOG_3BC(ERROR_INVALID_RETURN, "INVALID PROCEDURE RETURN");
        ERROR_LOG_3BC(
            ERROR_PARAM_DUALITY, "DUALITY ADDRES WITH VALUE IS NOT ALLOWED");
        ERROR_LOG_3BC(ERROR_PARAM_REQUIRE_ANY, "VALUE OR ADDRESS IS REQUIRED");
        ERROR_LOG_3BC(ERROR_PARAM_REQUIRE_VALUE, "VALUE IS REQUIRED");
        ERROR_LOG_3BC(ERROR_PARAM_REQUIRE_ADDRESS, "ADDRESS IS REQUIRED");
        ERROR_LOG_3BC(ERROR_PARAM_BLOCKED_VALUE, "VALUE IS NOT ALLOWED");
        ERROR_LOG_3BC(ERROR_PARAM_BLOCKED_ADDRESS, "ADDRESS IS NOT ALLOWED");
        ERROR_LOG_3BC(ERROR_NUMBER_NO_DIGITS, "NUMBER WHIOUT DIGITS");
        ERROR_LOG_3BC(ERROR_NUMBER_UNDERFLOW, "NUMBER UNDERFLOW");
        ERROR_LOG_3BC(ERROR_NUMBER_OVERFLOW, "NUMBER OVERFLOW");
        ERROR_LOG_3BC(ERROR_NUMBER_WRONG_BASE, "NUMBER WRONG BASE");
        ERROR_LOG_3BC(ERROR_NUMBER_NEGATIVE, "NUMBER NEGATIVE IS NOT EXPECTED");
        ERROR_LOG_3BC(ERROR_NUMBER_ZERO, "NUMBER ZERO IS NOT EXPECTED");
        ERROR_LOG_3BC(ERROR_OUT_OF_MEMORY, "OUT OF MEMORY");
        ERROR_LOG_3BC(ERROR_NONE_TTY, "NONE TTY");
        ERROR_LOG_3BC(ERROR_UNSUPPORTED, "UNSUPPORTED FEATURE");
        ERROR_LOG_3BC(ERROR_MEMORY_CONFIG, "MEMORY CONFIG");
        ERROR_LOG_3BC(ERROR_OPEN_FILE, "CANNOT OPEN FILE");
        ERROR_LOG_3BC(ERROR_NULL_POINTER, "NULL POINTER");
        ERROR_LOG_3BC(ERROR_CHAR_SCAPE, "INVALID CHARACTER ESCAPE");
        ERROR_LOG_3BC(ERROR_CHAR_SIZE, "INVALID CHARACTER SIZE");
        ERROR_LOG_3BC(ERROR_COLUMNS, "WRONG NUMBER OF COLUMNS");
    default:
        driver_tty_output_raw(app, app->tty_error, "UNKNOWN ERROR");
    }

    driver_tty_output_raw(app, app->tty_error, "\n");
#endif

    /** TODO: no closign when else **/
    if (error_code >= ERROR_CPU_ZERO) {
        driver_power_signal(SIGTERM);
    }
}

/**
 * run processor instructions,
 * this is a core of virtual machine
 */
void driver_program_tick(struct app_3bc_s* const app)
{
    instruction_3bc(app, app->program.curr->column.reg,
        app->program.curr->column.adr, app->program.curr->column.dta);

    /** go next line **/
    app->program.curr = app->program.curr->next;
}