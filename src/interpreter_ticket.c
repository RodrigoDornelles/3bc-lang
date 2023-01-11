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
void interpreter_ticket(tbc_app_st *const self)
{
    self->cache_l0.rx = TBC_EXIT;
}
#else
/**
 * Default entry point to the interpreter, works asynchronously.
 *
 * TODO: refactor single point of return, no implicit outputs.
 * TODO: do{} while(0);
 */
void interpreter_ticket(tbc_app_st *const self)
{
    int character = fgetc(self->cin.tty_source.io.stream);

#if defined(_3BC_NUTTX)
    if (self->cout.tty_source.type == STREAM_TYPE_COMPUTER_STD) {
        driver_tty_output(self, &self->cout.tty_keylog, STRC, character);
    }
#endif

    /** does nothing **/
    if (character == '\r') {
        self->cache_l0.rx = TBC_IGNORE;
        return;
    }

    /** end of file **/
    if ((character == EOF || character == -1)
        && self->cache_l3.buffer.storage == NULL) {
        self->cache_l0.rx = TBC_EXIT;
        return;
    }

    /** end of line **/
    if (character == '\n' || character == '\0' || character == EOF) {

        /** mark end of string **/
        {
            char* new_buffer = (char*)realloc(self->cache_l3.buffer.storage,
                sizeof(char) * (++self->cache_l3.buffer.size));
            if (new_buffer == NULL) {
                driver_program_error(self, ERROR_OUT_OF_MEMORY);
            } else {
                self->cache_l3.buffer.storage = new_buffer;
                self->cache_l3.buffer.storage[self->cache_l3.buffer.size - 1]
                    = '\0';
            }
        }

        /** insert to vm **/
        char* line = self->cache_l3.buffer.storage;
        do {
            fprintf(stderr, ".");
            self->program.last_line += 1;
            line = interpreter_readln(self, line);
        } while (line != NULL);

        self->pkg_func.prog.insert(self);

        /** reset buffer **/
        {
            free(self->cache_l3.buffer.storage);
            self->cache_l3.buffer.storage = NULL;
            self->cache_l3.buffer.size = 0;
        }

        self->cache_l0.rx = TBC_OK;
        return;
    }

    /** expand the  buffer **/
    {
        char* new_buffer = (char*)realloc(self->cache_l3.buffer.storage,
            sizeof(char) * (++self->cache_l3.buffer.size));

        if (new_buffer == NULL) {
            driver_program_error(self, ERROR_OUT_OF_MEMORY);
        } else {
            self->cache_l3.buffer.storage = new_buffer;
            self->cache_l3.buffer.storage[self->cache_l3.buffer.size - 1]
                = character;
        }
    }

    self->cache_l0.rx = TBC_REPEAT;
}
#endif
#endif
