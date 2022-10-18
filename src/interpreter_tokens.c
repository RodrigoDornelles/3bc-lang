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
 * Code refers to the interpreter where slice row into columns.
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
 * Separator in columns and rows.
 *
 * REFERENCE: 'reg' receive the first column
 * REFERENCE: 'mem' receive the second column
 * REFERENCE: 'val' receive the thirdy column
 * REFERENCE: 'line_end' NULL if the string is used completely.
 * REFERENCE: 'line_end' Pointer to the rest of the text if there are still
 * other lines. RETURN: true if the number of columns is valid. RETURN: true if
 * the number of columns is valid.
 *
 */
bool interpreter_tokens(
    char* line, char** reg, char** mem, char** val, char** line_end)
{
    unsigned char columns = 0;
    char* pointer = line;

    /** reset strings **/
    *line_end = NULL;
    *reg = NULL;
    *mem = NULL;
    *val = NULL;

    do {
        /** search for the beginning of the column **/
        while (strchr("\t. ", *pointer) != NULL && pointer[0] != '\0')
            ;
            pointer++;

        /** skip comments **/
        if (strchr("#;", *pointer) != NULL) {
            while (pointer[0] != '\n' && pointer[0] != '\0' && pointer[0] != EOF)
                ;
                pointer++;
            break;
        }

        /** end of line **/
        if ((pointer[0] == '\n' && pointer[1] == '\0') || pointer[0] == '\0') {
            break;
        }

        /** partial end of line **/
        if (pointer[0] == '\n' || pointer[0] == ',') {
            pointer[0] = '\0';
            *line_end = ++pointer;
            break;
        }

        /** insert columun **/
        switch (++columns) {
        case 1:
            *reg = pointer;
            break;

        case 2:
            *mem = pointer;
            break;

        case 3:
            *val = pointer;
            break;
        }

        /** skip literal char **/
        if (pointer[0] == '\'') {
            do {
                pointer++;
                if (pointer[0] == '\\') {
                    pointer++;
                }
            } while (pointer[0] != '\'' && pointer[0] != '\0');
        }

        /** skip other literals **/
        while (strchr("\t,. ", *pointer) == NULL && pointer[0] != '\0')
            ;
            pointer++;

        /** mark end of column **/
        if (pointer[0] != '\0' && pointer[0] != ',') {
            pointer[0] = '\0';
            pointer++;
        }
    } while (pointer[0] != '\0');

    /** validate number of columns **/
    return columns == 3 || columns == 0;
}
#endif
