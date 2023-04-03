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
 * Code refers to the interpreter where it reads a line, checks for problems,
 * and converts it to bytecode for use.
 *
 * DATASTRUCT:
 * Linked list, first in, first out.
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
#include "3bc.h"

#if defined(TBC_INTERPRETER) && !defined(TBC_SCU_OPTIONAL_FIX)
/**
 * Interpret text and insert to virtual machine.
 *
 * @todo refactor single point of return, no implicit outputs.
 * EXAMPLE: interpreter_compiler(app, "MODE 0 2");
 * RETURN: NULL if the entire string is compiled.
 * RETURN: Pointer to the rest of the string that can be compiled.
 */
char* interpreter_readln(struct app_3bc_s* const app, char* line)
{
    char *text_reg, *text_mem, *text_val;
    signed long int reg, mem, val;

    /** scan more 1 line**/
    if (!interpreter_tokens(line, &text_reg, &text_mem, &text_val, &line)) {
        driver_program_error(app, ERROR_COLUMNS);
    }
    /** blank line @todo not working!**/
    if (text_reg == NULL) {
        return line;
    }
    /** parse string to register and validate **/
    if (!interpreter_syntax_registers(app, text_reg, &reg)) {
        driver_program_error(app, ERROR_INVALID_REGISTER);
    }
    /** parse string to address and validate **/
    else if (!interpreter_syntax_constants(app, text_mem, &mem)) {
        driver_program_error(app, ERROR_INVALID_ADR);
    }
    /** parse string to constant and validate **/
    else if (!interpreter_syntax_constants(app, text_val, &val)) {
        driver_program_error(app, ERROR_INVALID_CONSTANT);
    } 
    
    /** add new line **/
    //ds_program_fifo_line_add(app, reg, mem, val);
    app->cpu.rx = reg;
    app->cpu.ry = mem;
    app->cpu.rz = val;

    return line;
}
#endif
