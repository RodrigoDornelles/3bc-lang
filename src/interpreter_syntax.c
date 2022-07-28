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
    /** passing register as numerical (octo, bin) **/
    if (interpreter_parser_strtol(app, string, value)) {
        return true;
    }

    /** mnemonic translate world to register **/
    switch (string[0] | (string[1] << 8) | (string[2] << 16) | (string[3] << 24)
        | 0x20202020) {
    case ('n' | ('i' << 8) | ((long)'l' << 16) | ((long)'l' << 24)):
        *value = NILL;
        return true;
    case ('m' | ('o' << 8) | ((long)'d' << 16) | ((long)'e' << 24)):
        *value = MODE;
        return true;

    case ('s' | 't' << 8) | ((long)'r' << 16) | ((long)'b' << 24):
        *value = STRB;
        return true;
    case ('s' | 't' << 8) | ((long)'r' << 16) | ((long)'i' << 24):
        *value = STRI;
        return true;
    case ('s' | 't' << 8) | ((long)'r' << 16) | ((long)'c' << 24):
        *value = STRC;
        return true;
    case ('s' | 't' << 8) | ((long)'r' << 16) | ((long)'o' << 24):
        *value = STRO;
        return true;
    case ('s' | 't' << 8) | ((long)'r' << 16) | ((long)'x' << 24):
        *value = STRX;
        return true;

    case ('f' | 'r' << 8) | ((long)'e' << 16) | ((long)'e' << 24):
        *value = FREE;
        return true;
    case ('a' | 'l' << 8) | ((long)'o' << 16) | ((long)'c' << 24):
        *value = ALOC;
        return true;
    case ('p' | 'u' << 8) | ((long)'l' << 16) | ((long)'l' << 24):
        *value = PULL;
        return true;
    case ('s' | 'p' << 8) | ((long)'i' << 16) | ((long)'n' << 24):
        *value = SPIN;
        return true;
    case ('p' | 'u' << 8) | ((long)'s' << 16) | ((long)'h' << 24):
        *value = PUSH;
        return true;

    case ('m' | 'o' << 8) | ((long)'f' << 16) | ((long)'f' << 24):
        *value = MOFF;
        return true;
    case ('m' | 'u' << 8) | ((long)'s' << 16) | ((long)'e' << 24):
        *value = MUSE;
        return true;

    case ('g' | 'o' << 8) | ((long)'t' << 16) | ((long)'o' << 24):
        *value = GOTO;
        return true;
    case ('f' | 'g' << 8) | ((long)'t' << 16) | ((long)'o' << 24):
        *value = FGTO;
        return true;
    case ('z' | 'g' << 8) | ((long)'t' << 16) | ((long)'o' << 24):
        *value = ZGTO;
        return true;
    case ('p' | 'g' << 8) | ((long)'t' << 16) | ((long)'o' << 24):
        *value = PGTO;
        return true;
    case ('n' | 'g' << 8) | ((long)'t' << 16) | ((long)'o' << 24):
        *value = NGTO;
        return true;

    case ('n' | 'b' << 8) | ((long)'0' << 16) | ((long)'2' << 24):
        *value = NB02;
        return true;
    case ('n' | 'b' << 8) | ((long)'0' << 16) | ((long)'8' << 24):
        *value = NB08;
        return true;
    case ('n' | 'b' << 8) | ((long)'1' << 16) | ((long)'0' << 24):
        *value = NB10;
        return true;
    case ('n' | 'b' << 8) | ((long)'1' << 16) | ((long)'6' << 24):
        *value = NB16;
        return true;

    case ('m' | 'a' << 8) | ((long)'t' << 16) | ((long)'h' << 24):
        *value = MATH;
        return true;

    case ('c' | 'a' << 8) | ((long)'l' << 16) | ((long)'l' << 24):
        *value = CALL;
        return true;
    case ('f' | 'c' << 8) | ((long)'a' << 16) | ((long)'l' << 24):
        *value = FCAL;
        return true;
    case ('z' | 'c' << 8) | ((long)'a' << 16) | ((long)'l' << 24):
        *value = ZCAL;
        return true;
    case ('p' | 'c' << 8) | ((long)'a' << 16) | ((long)'l' << 24):
        *value = PCAL;
        return true;
    case ('n' | 'c' << 8) | ((long)'a' << 16) | ((long)'l' << 24):
        *value = NCAL;
        return true;

    case ('f' | 'r' << 8) | ((long)'e' << 16) | ((long)'t' << 24):
        *value = FRET;
        return true;
    case ('z' | 'r' << 8) | ((long)'e' << 16) | ((long)'t' << 24):
        *value = ZRET;
        return true;
    case ('p' | 'r' << 8) | ((long)'e' << 16) | ((long)'t' << 24):
        *value = PRET;
        return true;
    case ('n' | 'r' << 8) | ((long)'e' << 16) | ((long)'t' << 24):
        *value = NRET;
        return true;
    case ('b' | 'a' << 8) | ((long)'c' << 16) | ((long)'k' << 24):
        *value = BACK;
        return true;

    case ('r' | 'e' << 8) | ((long)'a' << 16) | ((long)'l' << 24):
        *value = REAL;
        return true;
    case ('f' | 'a' << 8) | ((long)'k' << 16) | ((long)'e' << 24):
        *value = FAKE;
        return true;
    case ('m' | 'i' << 8) | ((long)'c' << 16) | ((long)'r' << 24):
        *value = MICR;
        return true;
    case ('m' | 'i' << 8) | ((long)'l' << 16) | ((long)'i' << 24):
        *value = MILI;
        return true;
    case ('s' | 'e' << 8) | ((long)'c' << 16) | ((long)'o' << 24):
        *value = SECO;
        return true;
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

    /** MAGICAL MNEMONIC NILL **/
    case ('s' | ('k' << 8) | ((long)'i' << 16) | ((long)'p' << 24)):
        *value = interpreter_parser_skip();
        return true;
    }

    return false;
}
#endif
