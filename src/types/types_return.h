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
 * @todo describre.
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

#ifndef H_TYPES_RETURN_TBC
#define H_TYPES_RETURN_TBC

/**
 * @li equal @c 0 is normal operation.
 * @li after @c 1 is status communication.
 * @li after @c 128 is interrupt.
 * @li after @c 192 is blocking interrupt.
 * @note the <b> blocking interrupt </b> is the fact that it
 * does not allow the @b CPU to execute until another non-blocking return.
 */
enum ___tbc_return_e {
    TBC_RET_OK = 0,
    TBC_RET_REPEAT = 1,
    TBC_RET_IGNORE = 2,
    TBC_RET_CLEAN = 3,
    TBC_RET_FULL = 4,
    TBC_RET_GC_OK = 5,
    TBC_RET_CATCH_ERROR = 6,
    TBC_RET_RELOAD = 7,
    TBC_RET_EXIT_SAFE = 129,
    TBC_RET_EXIT_FORCE = 130,
    TBC_RET_PRINT_ERROR_1 = 131,
    TBC_RET_PRINT_ERROR_2 = 132,
    TBC_RET_PRINT_ERROR_3 = 133,
    TBC_RET_PRINT_ERROR_4 = 134,
    TBC_RET_PRINT_ERROR_5 = 135,
    TBC_RET_PRINT_ERROR_6 = 136,
    TBC_RET_PRINT_ERROR_7 = 137,
    TBC_RET_PRINT_ERROR_8 = 138,
    TBC_RET_PRINT_ERROR_9 = 139,
    TBC_RET_PRINT_ERROR_A = 140,
    TBC_RET_PRINT_ERROR_B = 141,
    TBC_RET_PRINT_ERROR_C = 142,
    TBC_RET_PRINT_ERROR_D = 143,
    TBC_RET_PRINT_ERROR_E = 144,
    TBC_RET_PRINT_ERROR_F = 145,
    TBC_RET_SYS_MATH = 186,
    TBC_RET_SYS_MEM_READ = 187,
    TBC_RET_SYS_MEM_WRITE = 188,
    TBC_RET_SYS_IO_READ = 189,
    TBC_RET_SYS_IO_WRITE = 190,
    TBC_RET_SYS_WAIT = 191,
    TBC_RET_THROW_ERROR = 192,
    TBC_RET_GC_END = 250,
    TBC_RET_GC_LV1 = 251,
    TBC_RET_GC_LV2 = 252,
    TBC_RET_GC_LV3 = 253,
    TBC_RET_GC_LV4 = 254,
    TBC_RET_END = 255
};

typedef enum ___tbc_return_e tbc_return_et;

#endif
