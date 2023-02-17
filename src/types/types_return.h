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
 * TODO: describre.
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

enum ___tbc_return_e {
    TBC_RET_ERROR = - 4,
    TBC_RET_OUT_MEM = -3,
    TBC_RET_EXIT_FORCE = -2,
    TBC_RET_EXIT = -1,
    TBC_RET_OK = 0,
    TBC_RET_GC_LV1 = 1,
    TBC_RET_GC_LV2 = 2,
    TBC_RET_GC_LV3 = 3,
    TBC_RET_GC_LV4 = 4,
    TBC_RET_GC_END = 5,
    TBC_RET_REPEAT = 6,
    TBC_RET_IGNORE = 7,
    TBC_RET_CLEAN = 8,
    TBC_RET_FULL = 9,
    TBC_RET_SYSCALL = 10
};

typedef enum ___tbc_return_e tbc_return_et;

#endif
