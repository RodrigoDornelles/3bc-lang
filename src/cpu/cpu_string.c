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
 * Code refers registers for text manipulation.
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

#include "3bc.h"

static void cpu_string_output(struct app_3bc_s* const self);

tbc_method_ft ___cpu_string_layout[] = {
    cpu_string_output, cpu_string_output, cpu_string_output,
    cpu_string_output, cpu_string_output
};

const unsigned char cpu_string_layout_size = sizeof(___cpu_string_layout);
const void* cpu_string_layout_opcodes = ___cpu_string_layout;

/**
 * @todo refact
 */
void cpu_string_debug(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    driver_tty_output(app, &app->cout.tty_debug, reg, GET_ANY_PARAM);
}

void cpu_string_output(struct app_3bc_s* const self)
{
    do {
        if (self->cache_l1.syscall == TBC_SYS_NONE) {
            if (self->cache_l0.ry) {
                if (self->cache_l0.rz) {
                    /* ry && rz */
                    driver_program_error(self, ERROR_PARAM_DUALITY);
                    break;
                } 
                /* ry */
                self->rc = TBC_RET_SYSCALL;
                self->cache_l1.syscall = TBC_SYS_MEM_READ;
                break;
            } 
            else {
                /* rz */
                self->mem_aux = self->cache_l0.rz;
            }
        }

        if (self->cache_l1.syscall != TBC_SYS_IO_WRITE) {
            char* out = self->cache_l3.fixbuf.storage;
            static const size_t out_size = sizeof(self->cache_l3.fixbuf.storage);

            if (self->cache_l0.rx == STRC)
            {
                self->cache_l3.fixbuf.size = 1;
                self->cache_l3.fixbuf.storage[0] = self->mem_aux;
            }
            else {
                /** @todo fix negative bit **/
                if (self->mem_aux & 0b10000000) {
                    out += 1;
                    self->mem_aux = (tbc_u8_t) -self->mem_aux;
                    self->cache_l3.fixbuf.size += 1;
                    self->cache_l3.fixbuf.storage[0] = '-';
                }
                switch(self->cache_l0.rx)
                {
                    case STRO:
                        self->cache_l3.fixbuf.size += snprintf(out, out_size, "%o", (unsigned int) self->mem_aux);
                        break;

                    case STRI:
                        self->cache_l3.fixbuf.size += snprintf(out, out_size, "%u", (unsigned int) self->mem_aux);
                        break;

                    case STRX:
                        self->cache_l3.fixbuf.size += snprintf(out, out_size, "%x", (unsigned int) self->mem_aux);
                        break;                    
                }
            }
            self->cache_l2.tty = &(self->cout.tty_output);
            self->cache_l1.syscall = TBC_SYS_IO_WRITE;
            self->rc = TBC_RET_SYSCALL;
            break;
        }

        self->rc = TBC_RET_GC_LV3;
        break;
    }
    while (0);
}

void cpu_string_input(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    {
        data_3bc_t aux = driver_tty_input(app, &app->cin.tty_input, reg);
        driver_accumulator_set(app, aux);
        driver_memory_data_set(app, address, aux);
        driver_tty_output(app, &app->cout.tty_keylog, reg, aux);
    }
}

void cpu_string_input_silent(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    {
        data_3bc_t aux = driver_tty_input(app, &app->cin.tty_input, reg);
        driver_accumulator_set(app, aux);
        driver_memory_data_set(app, address, aux);
    }
}

void cpu_string_input_password(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    {
        data_3bc_t aux = driver_tty_input(app, &app->cin.tty_input, reg);
        driver_accumulator_set(app, aux);
        driver_memory_data_set(app, address, aux);
        driver_tty_output(app, &app->cout.tty_keylog, STRC, '*');
    }
}
