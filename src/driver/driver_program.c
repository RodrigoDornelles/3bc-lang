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
 * @todo
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
static const char error_header[]
    = "\n\n[3BC] %03d Fatal error 0x%06X in line: %06u\n";
#else
static const char error_header[]
    = "\n[3BC] CRITICAL ERROR ABORTED THE PROGRAM\n> MACHINE ID:\t"
#if defined(TBC_ID_64_BITS) || defined(TBC_ID_32_BITS)
      "%08lu"
#elif defined(TBC_ID_16_BITS) || defined(TBC_ID_8_BITS)
      "%08u"
#endif
      "\n> ERROR LINE:\t%08u\n> ERROR CODE:\t0x%06X\n> DESCRIPTION: ";
#endif

void driver_program_error(
    struct app_3bc_s* const app, tbc_error_et error_code)
{
    /**
     * NOTE: if the current line does not exist,
     * it was because it was interpreting a line which failed.
     *
     * @todo
     * safer and remove ternaries.
     */
    line_3bc_t error_line
        = app->program.curr != NULL && error_code >= ERROR_CPU_ZERO
        ? app->program.curr->line
        : app->program.last_line;

    /** print header of error**/
    char error_code_string[sizeof(error_header) + 11];
    snprintf(error_code_string, sizeof(error_code_string), error_header, app->id,
        error_line, error_code);
    driver_tty_output_raw(app, &app->cout.tty_error, error_code_string);

    /** @todo not use macros and move to 3bc_errors.h **/
    driver_tty_output_raw(app, &app->cout.tty_error, "aaa\n");

    /** @todo no closign when else **/
    if (error_code >= ERROR_CPU_ZERO) {
        driver_power_signal(SIGTERM);
    }
}
