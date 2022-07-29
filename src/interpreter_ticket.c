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
 * Code refers to the interpreter where accumulates buffer per machine cycle.
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

#if !defined(TBC_SCU_OPTIONAL_FIX)
/**
 * JOKE: rest in peace spaghetti code, I won't miss you.
 */
#if !defined(TBC_INTERPRETER)
/**
 * When interpreter disabled, always returns end of file.
 */
int interpreter_ticket(struct app_3bc_s* const app)
{
    return EOF;
}
#else
/**
 * Default entry point to the interpreter, works asynchronously.
 *
 * RETURN: CR if does nothing.
 * RETURN: EOF if there is nothing else to read.
 * RETURN: 1 if the interpretation was successful.
 */
int interpreter_ticket(struct app_3bc_s* const app)
{
    int character = fgetc(app->tty_source.io.stream);

#if defined(_3BC_NUTTX)
    if (app->tty_source.type == STREAM_TYPE_COMPUTER_STD) {
        driver_tty_output(app, app->tty_keylog, STRC, character);
    }
#endif

    /** does nothing **/
    if (character == '\r') {
        return '\r';
    }

    /** end of file **/
    if ((character == EOF || character == -1) && app->cache_l3.buffer.storage == NULL) {
        return EOF;
    }

    /** end of line **/
    if (character == '\n' || character == '\0' || character == EOF) {

        /** mark end of string **/
        {
            char* new_buffer = (char*)realloc(app->cache_l3.buffer.storage,
                sizeof(char) * (++app->cache_l3.buffer.size));
            if (new_buffer == NULL) {
                driver_program_error(app, ERROR_OUT_OF_MEMORY);
            }
            app->cache_l3.buffer.storage = new_buffer;
            app->cache_l3.buffer.storage[app->cache_l3.buffer.size - 1] = '\0';
        }

        /** insert to vm **/
        char* line = app->cache_l3.buffer.storage;
        do {
            app->program.last_line += 1;
            line = interpreter_readln(app, line);
        } while (line != NULL);

        /** reset buffer **/
        {
            free(app->cache_l3.buffer.storage);
            app->cache_l3.buffer.storage = NULL;
            app->cache_l3.buffer.size = 0;
        }

        return 1;
    }

    /** expand the  buffer **/
    {
        char* new_buffer = (char*)realloc(app->cache_l3.buffer.storage,
            sizeof(char) * (++app->cache_l3.buffer.size));

        if (new_buffer == NULL) {
            driver_program_error(app, ERROR_OUT_OF_MEMORY);
        }

        app->cache_l3.buffer.storage = new_buffer;
        app->cache_l3.buffer.storage[app->cache_l3.buffer.size - 1] = character;
    }

    return 0;
}
#endif
#endif
