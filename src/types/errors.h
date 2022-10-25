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

#ifndef H_ERRORS_TBC
#define H_ERRORS_TBC

typedef enum __tbc_error_e tbc_error_et;

enum ___tbc_error_e {
    ERROR_CPU_ZERO = 1,
    ERROR_CPU_RESERVED,
    ERROR_INVALID_REGISTER,
    ERROR_INVALID_ADDRESS,
    ERROR_INVALID_CONSTANT,
    ERROR_INVALID_CPU_MODE,
    ERROR_INVALID_LABEL,
    ERROR_INVALID_RETURN,
    ERROR_PARAM_DUALITY,
    ERROR_PARAM_REQUIRE_ANY,
    ERROR_PARAM_REQUIRE_VALUE,
    ERROR_PARAM_REQUIRE_ADDRESS,
    ERROR_PARAM_BLOCKED_VALUE,
    ERROR_PARAM_BLOCKED_ADDRESS,
    ERROR_NUMBER_NO_DIGITS,
    ERROR_NUMBER_UNDERFLOW,
    ERROR_NUMBER_OVERFLOW,
    ERROR_NUMBER_WRONG_BASE,
    ERROR_NUMBER_NEGATIVE,
    ERROR_NUMBER_ZERO,
    ERROR_OUT_OF_MEMORY,
    ERROR_NONE_TTY,
    ERROR_UNSUPPORTED,
    ERROR_MEMORY_CONFIG,
    ERROR_OPEN_FILE,
    ERROR_NULL_POINTER,
    ERROR_CHAR_SCAPE,
    ERROR_CHAR_SIZE,
    ERROR_COLUMNS
};

#endif
