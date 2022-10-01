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
 * Code refers to the interpreter where it parses syntax
 * and discovers literal types.
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
 *
 * NOTE:
 * The number 0x202020 is equivalent to (32|32<<8|32<<16|32<<24),
 * makes the 4 characters are forced to be lowercase at the same time.
 *
 * The expression ('b'|('a'<<8)|((long)'a'<<16)|((long)'z'<<24))
 * it's like a 'baaz' multichar without the worry of incompatibility,
 * or bigendian/litleendian issues.
 *
 */

#define TBC_SOURCE_ENTRY
#include "3bc.h"

#if defined(TBC_INTERPRETER) && !defined(TBC_SCU_OPTIONAL_FIX)

/**
 * BRIEF:
 * representation of the menomonics for registers
 * with their respective opcodes.
 *
 * NOTE:
 * must be ordered.
 *
 * JOKE:
 * why you need for CPP if C language is already 'complete and total'?
 * { .keyword.name = "mode", .opcode = 7 } <-- not allowed in C++
 */
static const struct tbc_keyword_opcode_st opcodes_register[] = { { "aloc", 2 },
    { "back", 1 }, { "call", 1 }, { "fake", 2 }, { "fcal", 2 }, { "fgto", 2 },
    { "free", 1 }, { "fret", 2 }, { "goto", 1 }, { "math", 1 }, { "micr", 3 },
    { "mili", 4 }, { "mode", 7 }, { "moff", 3 }, { "muse", 4 }, { "nb02", 1 },
    { "nb08", 2 }, { "nb10", 3 }, { "nb16", 4 }, { "ncal", 5 }, { "ngto", 5 },
    { "nill", 0 }, { "nret", 5 }, { "pcal", 4 }, { "pgto", 4 }, { "pret", 4 },
    { "pull", 3 }, { "push", 5 }, { "real", 1 }, { "seco", 5 }, { "spin", 4 },
    { "strb", 1 }, { "strc", 5 }, { "stri", 3 }, { "stro", 2 }, { "strx", 4 },
    { "zcal", 3 }, { "zgto", 3 }, { "zret", 3 } };

static const tbc_i8_t opcodes_register_size
    = sizeof(opcodes_register) / sizeof(struct tbc_keyword_opcode_st);

/**
 * BRIEF:
 * representation of the menomonics for constant
 * with their respective opcodes.
 */

/** nill (0) constant menomonic **/
static const union tbc_keyword_ut opcode_constant_nill = { "nill" };

/** full (1023) constant menomonic **/
static const union tbc_keyword_ut opcode_constant_full = { "full" };

/** skip (?) magic menomonic **/
static const union tbc_keyword_ut opcode_constant_skip = { "skip" };

/**
 * Checks menomics and literal expressions of the first column only.
 *
 * NOTE:
 * This algorithm has endians-independent math.
 * https://developer.ibm.com/articles/au-endianc
 *
 * NOTE:
 * This method does not need to be protected,
 * as it will be executed only if there are 3 columns,
 * which would be at least 5 characters.
 *
 */
bool interpreter_syntax_registers(struct app_3bc_s* const app,
    const char* const string, signed long int* value)
{
    tbc_i8_t mid;
    tbc_i32_t result;
    tbc_i8_t low = 0;
    bool success = false;
    union tbc_keyword_ut key;
    tbc_i8_t high = opcodes_register_size;

    /** single return point **/
    do {
        /** passing register as numerical (octo, bin) **/
        if (interpreter_parser_strtol(app, string, value)) {
            success = true;
            break;
        }

        /** copy reversed **/
        key.name[0] = string[3];
        key.name[1] = string[2];
        key.name[2] = string[1];
        key.name[3] = string[0];

        /** force to lowercase **/
        key.compare |= 0x20202020;

        /** binary search **/
        do {
            /** find middle **/
            mid = (low + high) / 2;

            /** force litle endian sub **/
            result = 0;
            result |= opcodes_register[mid].keyword.name[3];
            result |= opcodes_register[mid].keyword.name[2] << 8;
            result |= opcodes_register[mid].keyword.name[1] << 16;
            result |= opcodes_register[mid].keyword.name[0] << 24;
            result -= *(tbc_i32_t*)&key.compare;

            /** found **/
            if (result == 0) {
                *value = opcodes_register[mid].opcode;
                success = true;
                break;
            }
            /** on left **/
            if (result > 0) {
                high = mid - 1;
            }
            /** on right **/
            if (result < 0) {
                low = mid + 1;
            }
        } while (low <= high);
    } while (0);

    return success;
}

/**
 * Checks menomics and literal expressions of the second and last column.
 */
bool interpreter_syntax_constants(struct app_3bc_s* const app,
    const char* const string, signed long int* value)
{
    bool success = false;

    /** single return point **/
    do {
        /** prevent ilegal pointer **/
        if (string == NULL) {
            break;
        }
        /** is safe! **/
        if (interpreter_parser_strtol(app, string, value)) {
            success = true;
            break;
        }
        /** is safe! **/
        if (interpreter_parser_strhash(string, value)) {
            success = true;
            break;
        }
        /** prevent memory invasion **/
        if (string[1] == '\0' || string[2] == '\0') {
            break;
        }
        /** is not safe, but now it's protected. **/
        if (interpreter_parser_strchar(app, string, value)) {
            success = true;
            break;
        }
        /** more memory prevention, remembering previous results **/
        if (string[3] == '\0') {
            break;
        }

        /** menomonics **/
        {
            /** copy normal **/
            union tbc_keyword_ut key;
            key.name[0] = string[0];
            key.name[1] = string[1];
            key.name[2] = string[2];
            key.name[3] = string[3];

            /** force to lowercase **/
            key.compare |= 0x20202020;

            /** integer compare menomonics 'NILL' **/
            if (key.compare == opcode_constant_nill.compare) {
                *value = NILL;
                success = true;
                break;
            }

            /** integer compare menomonics 'SKIP' **/
            if (key.compare == opcode_constant_skip.compare) {
                *value = interpreter_parser_skip();
                success = true;
                break;
            }

            /** integer compare menomonics 'FULL' **/
            if (key.compare == opcode_constant_full.compare) {
                *value = 1023;

                success = true;
                break;
            }
        }
    } while (0);

    return success;
}
#endif
