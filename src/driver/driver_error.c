/**
 * @internal
 *  ___________  _____   _
 * |____ | ___ \/  __ \ | |
 *     / / |_/ /| /  \/ | | __ _ _ __   __ _ _   _  __ _  __ _  ___
 *     \ \ ___ \| |     | |/ _` | '_ \ / _` | | | |/ _` |/ _` |/ _ \
 * .___/ / |_/ /| \__/\ | | (_| | | | | (_| | |_| | (_| | (_| |  __/
 * \____/\____/  \____/ |_|\__,_|_| |_|\__, |\__,_|\__,_|\__, |\___|
 *                                     __/ |             __/ |
 *                                    |___/             |___/
 * @endinternal
 * @file driver_error.c
 *
 * @brief
 * handler and report runtime errors.
 *
 * @copyright
 * Low-level language, tiny virtual machine, intermediate representation,     \n
 * embeddable, easy for beginners. (Friendly Punched cards)                   \n
 *                                                                            \n
 * Copyright (C) 2020 Rodrigo Dornelles.                                      \n
 *                                                                            \n
 * This program is free software: you can redistribute it and/or modify       \n
 * it under the terms of the GNU General Public License as published by       \n
 * the Free Software Foundation, either version 3 of the License,             \n
 * or any later version.                                                      \n
 *                                                                            \n
 * This program is distributed in the hope that it will be useful,            \n
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             \n
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              \n
 * GNU General Public License for more details.                               \n
 *                                                                            \n
 * You should have received a copy of the GNU General Public License          \n
 * along with this program.  If not, see <https://www.gnu.org/licenses/>. 
 *
 */
#include "i18n_0000.h"
#include "cast_itos.h"
#include "driver_error.h"

static const char ___msg_err_1[] = "[3BC] CRITICAL ERROR ABORTED THE PROGRAM";
static const char ___msg_err_2[] = "\n> MACHINE ID:\t";
static const char ___msg_err_4[] = "\n> ERROR LINE:\t";
static const char ___msg_err_6[] = "\n> ERROR CODE:\t";
static const char ___msg_err_8[] = "\n> DESCRIPTION:\t";
static const tbc_u8_t ___len_err_1 = (tbc_u8_t) (sizeof(___msg_err_1) * (-1));
static const tbc_u8_t ___len_err_2 = (tbc_u8_t) (sizeof(___msg_err_2) * (-1));
static const tbc_u8_t ___len_err_4 = (tbc_u8_t) (sizeof(___msg_err_4) * (-1));
static const tbc_u8_t ___len_err_6 = (tbc_u8_t) (sizeof(___msg_err_6) * (-1));
static const tbc_u8_t ___len_err_8 = (tbc_u8_t) (sizeof(___msg_err_8) * (-1));

/**
 * @startuml
 * (*) --> "Throw error"
 * --> "Print error (part 1..10)"
 * --> "Garbage Collector"
 * --> (*)
 * @enduml
 */
void driver_error(struct app_3bc_s* const self)
{
    do {
        if (TBC_RET_PRINT_ERROR_1 <= self->rc &&
            self->rc <= TBC_RET_PRINT_ERROR_F) {
            self->cache_l2.tty = &(self->cout.tty_output);
            ++self->rc;
        }

        if (self->rc == TBC_RET_THROW_ERROR) {
            self->rc = TBC_RET_PRINT_ERROR_1;
        }

        if (self->rc == TBC_RET_PRINT_ERROR_1) {
            self->cache_l3.buffer.storage = (char*) ___msg_err_1;
            self->cache_l3.buffer.size = ___len_err_1;
            break;
        }

        if (self->rc == TBC_RET_PRINT_ERROR_2) {
            self->cache_l3.buffer.storage = (char*) ___msg_err_2;
            self->cache_l3.buffer.size = ___len_err_2;
            break;
        }

        if (self->rc == TBC_RET_PRINT_ERROR_3) {
            self->cache_l3.fixbuf.size = 
                cast_itos10(
                    self->cache_l3.fixbuf.storage,
                    &self->id,
                    sizeof(self->cache_l3.fixbuf.storage),
                    sizeof(self->id) * 8
                );
            break;
        }
        
        if (self->rc == TBC_RET_PRINT_ERROR_4) {
            self->cache_l3.buffer.storage = (char*) ___msg_err_4;
            self->cache_l3.buffer.size = ___len_err_4;
            break;
        }

        if (self->rc == TBC_RET_PRINT_ERROR_5) {
            self->cache_l3.fixbuf.size = 
                cast_itos10(
                    self->cache_l3.fixbuf.storage,
                    &self->cin.tty_storage.io.arr.index,
                    sizeof(self->cache_l3.fixbuf.storage),
                    sizeof(self->cin.tty_storage.io.arr.index) * 8
                );
            break;
        }

        if (self->rc == TBC_RET_PRINT_ERROR_6) {
            self->cache_l3.buffer.storage = (char*) ___msg_err_6;
            self->cache_l3.buffer.size = ___len_err_6;
            break;
        }

        if (self->rc == TBC_RET_PRINT_ERROR_7) {
            self->cache_l3.fixbuf.size = 
                cast_itos10(
                    self->cache_l3.fixbuf.storage,
                    &self->cache_l1.error,
                    sizeof(self->cache_l3.fixbuf.storage),
                    sizeof(self->cache_l1.error) * 8
                );
            break;
        }

        if (self->rc == TBC_RET_PRINT_ERROR_8) {
            self->cache_l3.buffer.storage = (char*) ___msg_err_8;
            self->cache_l3.buffer.size = ___len_err_8;
            break;
        }

        if (self->rc == TBC_RET_PRINT_ERROR_9) {
            if (self->cache_l1.error >= tbc_i18n_error_len) {
                self->cache_l1.error = 0;
            }
            self->cache_l3.buffer.size =
                -tbc_i18n_error_arr[self->cache_l1.error].len;
            self->cache_l3.buffer.storage =
                tbc_i18n_error_arr[self->cache_l1.error].ptr;
            break;
        }

        if (self->rc == TBC_RET_PRINT_ERROR_A) {
            self->cache_l3.fixbuf.size = 1;
            self->cache_l3.fixbuf.storage[0] = '\n';
            break;
        }

        if (self->rc == TBC_RET_PRINT_ERROR_B) {
            self->rc = TBC_RET_GC_LV3;
            break;
        }

        self->rc = TBC_RET_OK;
    }
    while(0);
}
