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
 */
static const struct tbc_keyword_opcode_st keywords_opcode[] = {
    /** COMMON CPU MODES **/
    { "nill", 0 }, { "mode", 7 },
    /** CPU MODE 1..5 **/
    { "strb", 1 }, { "stro", 2 }, { "stri", 3 }, { "strx", 4 }, { "strc", 5 },
    /** CPU MODE 6..8 **/
    { "free", 1 }, { "aloc", 2 },
    /** CPU MODE 6**/
    { "moff", 3 }, { "muse", 4 },
    /** CPU MODE 7,8 **/
    { "pull", 3 }, { "spin", 4 }, { "push", 5 },
    /** CPU MODE 9 **/
    { "goto", 1 }, { "fgto", 2 }, { "zgto", 3 }, { "pgto", 4 }, { "ngto", 5 },
    /** CPU MODE 11..18,21..29,31..39 **/
    { "math", 1 },
    /** CPU MODE 29 **/
    { "nb02", 1 }, { "nb08", 2 }, { "nb10", 3 }, { "nb16", 4 },
    /** CPU MODE 41 **/
    { "back", 1 }, { "fret", 2 }, { "zret", 3 }, { "pret", 4 }, { "nret", 5 },
    /** CPU MODE 42 **/
    { "call", 1 }, { "fcal", 2 }, { "zcal", 3 }, { "pcal", 4 }, { "ncal", 5 },
    /** CPU MODE 43,44 **/
    { "seco", 5 },
    /** CPU MODE 43 **/
    { "real", 1 }, { "fake", 2 }, { "micr", 3 }, { "mili", 4 }
};

static const char keywords_opcode_size
    = sizeof(keywords_opcode) / sizeof(struct tbc_keyword_opcode_st);

/**
 * Checks menomics and literal expressions of the first column only.
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
    tbc_u8_t i = 0;
    tbc_keyword_ut key;

    /** passing register as numerical (octo, bin) **/
    if (interpreter_parser_strtol(app, string, value)) {
        return true;
    }

    /** copy keyname **/
    memcpy(key.name, string, 5);
    /** force to lowercase **/
    key.compare |= 0x20202020;

    /** each register menomonic **/
    while (i < keywords_opcode_size) {
        /** compare keywords are same **/
        if (keywords_opcode[i].keyword.compare == key.compare) {
            /** get value **/
            *value = keywords_opcode[i].opcode;
            return true;
        }
        /** increment before **/
        i++;
    }

    return false;
}

/**
 * Checks menomics and literal expressions of the second and last column.
 */
bool interpreter_syntax_constants(struct app_3bc_s* const app,
    const char* const string, signed long int* value)
{
    /** is safe! **/
    if (interpreter_parser_strtol(app, string, value)) {
        return true;
    }
    /** is safe! **/
    if (interpreter_parser_strhash(string, value)) {
        return true;
    }
    /** prevent memory invasion **/
    if (string[1] == '\0' || string[2] == '\0') {
        return false;
    }
    /** is not safe, but now it's protected. **/
    if (interpreter_parser_strchar(app, string, value)) {
        return true;
    }
    /** more memory prevention, remembering previous results **/
    if (string[3] == '\0') {
        return false;
    }

    /** is not safe! **/
    switch (string[0] | (string[1] << 8) | (string[2] << 16) | (string[3] << 24)
        | 0x20202020) {

    /** MNEMONIC NILL **/
    case ('n' | ('i' << 8) | ((long)'l' << 16) | ((long)'l' << 24)):
        *value = NILL;
        return true;

    /** MNEMONIC NILL **/
    case ('f' | ('u' << 8) | ((long)'l' << 16) | ((long)'l' << 24)):
        *value = 1023;
        return true;

    /** MAGICAL MNEMONIC NILL **/
    case ('s' | ('k' << 8) | ((long)'i' << 16) | ((long)'p' << 24)):
        *value = interpreter_parser_skip();
        return true;
    }

    return false;
}
#endif
