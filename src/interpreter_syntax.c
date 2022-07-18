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
 */

#define TBC_SOURCE_ENTRY
#include "3bc.h"

#if defined(TBC_INTERPRETER) && !defined(TBC_SCU_OPTIONAL_FIX)
bool interpreter_syntax_registers(
    struct app_3bc_s* const app, const char* string, signed long int* value)
{
    /** mnemonic translate world to register **/
    switch (PARSER_UNPACK(string)) {
        PARSER_PACK('n', 'i', 'l', 'l', value, NILL);
        PARSER_PACK('m', 'o', 'd', 'e', value, MODE);

        PARSER_PACK('s', 't', 'r', 'b', value, STRB);
        PARSER_PACK('s', 't', 'r', 'i', value, STRI);
        PARSER_PACK('s', 't', 'r', 'c', value, STRC);
        PARSER_PACK('s', 't', 'r', 'o', value, STRO);
        PARSER_PACK('s', 't', 'r', 'x', value, STRX);

        PARSER_PACK('f', 'r', 'e', 'e', value, FREE);
        PARSER_PACK('a', 'l', 'o', 'c', value, ALOC);
        PARSER_PACK('p', 'u', 'l', 'l', value, PULL);
        PARSER_PACK('s', 'p', 'i', 'n', value, SPIN);
        PARSER_PACK('p', 'u', 's', 'h', value, PUSH);

        PARSER_PACK('m', 'o', 'f', 'f', value, MOFF);
        PARSER_PACK('m', 'u', 's', 'e', value, MUSE);

        PARSER_PACK('g', 'o', 't', 'o', value, GOTO);
        PARSER_PACK('f', 'g', 't', 'o', value, FGTO);
        PARSER_PACK('z', 'g', 't', 'o', value, ZGTO);
        PARSER_PACK('p', 'g', 't', 'o', value, PGTO);
        PARSER_PACK('n', 'g', 't', 'o', value, NGTO);

        PARSER_PACK('n', 'b', '0', '2', value, NB02);
        PARSER_PACK('n', 'b', '0', '8', value, NB08);
        PARSER_PACK('n', 'b', '1', '0', value, NB10);
        PARSER_PACK('n', 'b', '1', '6', value, NB16);

        PARSER_PACK('m', 'a', 't', 'h', value, MATH);

        PARSER_PACK('c', 'a', 'l', 'l', value, CALL);
        PARSER_PACK('f', 'c', 'a', 'l', value, FCAL);
        PARSER_PACK('z', 'c', 'a', 'l', value, ZCAL);
        PARSER_PACK('p', 'c', 'a', 'l', value, PCAL);
        PARSER_PACK('n', 'c', 'a', 'l', value, NCAL);

        PARSER_PACK('f', 'r', 'e', 't', value, FRET);
        PARSER_PACK('z', 'r', 'e', 't', value, ZRET);
        PARSER_PACK('p', 'r', 'e', 't', value, PRET);
        PARSER_PACK('n', 'r', 'e', 't', value, NRET);
        PARSER_PACK('b', 'a', 'c', 'k', value, BACK);

        PARSER_PACK('r', 'e', 'a', 'l', value, REAL);
        PARSER_PACK('f', 'a', 'k', 'e', value, FAKE);
        PARSER_PACK('m', 'i', 'c', 'r', value, MICR);
        PARSER_PACK('m', 'i', 'l', 'i', value, MILI);
        PARSER_PACK('s', 'e', 'c', 'o', value, SECO);
    }

    /** passing register as numerical (octo, bin) **/
    if (interpreter_parser_strtol(app, string, value)) {
        return true;
    }

    return false;
}

bool interpreter_syntax_constants(
    struct app_3bc_s* const app, const char* string, signed long int* value)
{
    switch (PARSER_UNPACK(string)) {
        PARSER_PACK('n', 'i', 'l', 'l', value, NILL);
        PARSER_PACK('f', 'u', 'l', 'l', value, SHRT_MAX);
        PARSER_PACK('s', 'k', 'i', 'p', value, interpreter_parser_skip());
    }

    if (interpreter_parser_strtol(app, string, value)) {
        return true;
    } else if (interpreter_parser_strchar(app, string, value)) {
        return true;
    } else if (interpreter_parser_strhash(string, value)) {
        return true;
    }

    return false;
}
#endif
