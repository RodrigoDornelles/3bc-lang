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
 * Header refers to errors codes and messages.
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

#ifndef H_TYPES_ERRORS_TBC
#define H_TYPES_ERRORS_TBC

enum ___tbc_error_e {
    ERROR_UNKNOWN = 0,
    ERROR_CPU_ZERO = 1,
    ERROR_CPU_RESERVED = 2,
    ERROR_INVALID_REGISTER = 3,
    ERROR_INVALID_ADR = 4,
    ERROR_INVALID_CONSTANT = 5,
    ERROR_INVALID_CPU_MODE = 6,
    ERROR_INVALID_LABEL_3BC = 7,
    ERROR_INVALID_RETURN = 8,
    ERROR_PARAM_DUALITY = 9,
    ERROR_PARAM_REQUIRE_ANY = 10,
    ERROR_PARAM_REQUIRE_VALUE = 11,
    ERROR_PARAM_REQUIRE_ADDRESS = 12,
    ERROR_PARAM_BLOCKED_VALUE = 13,
    ERROR_PARAM_BLOCKED_ADDRESS = 14,
    ERROR_NUMBER_NO_DIGITS = 15,
    ERROR_NUMBER_UNDERFLOW = 16,
    ERROR_NUMBER_OVERFLOW = 17,
    ERROR_NUMBER_WRONG_BASE = 18,
    ERROR_NUMBER_NEGATIVE = 19,
    ERROR_NUMBER_ZERO = 20,
    ERROR_NUMBER_INVALID_BASE = 21,
    ERROR_NONE_TTY = 22,
    ERROR_UNSUPPORTED = 23,
    ERROR_MEMORY_CONFIG = 24,
    ERROR_OPEN_FILE = 25,
    ERROR_NULL_POINTER = 26,
    ERROR_CHAR_SCAPE = 27,
    ERROR_CHAR_SIZE = 28,
    ERROR_COLUMNS = 29,
    ERROR_MEM_STACK_CFG_MIS = 30,
    ERROR_MEM_STACK_CFG_MIN = 31,
    ERROR_MEM_STACK_CFG_OUT = 32,
    ERROR_OUT_OF_MEMORY = 33,
    ERROR_FLAG_LINE = 34,
    ERROR_INVALID_SYNTAX = 35
};

typedef enum ___tbc_error_e tbc_error_et;

#endif
