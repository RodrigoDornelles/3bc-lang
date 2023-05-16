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
#include "cast_itos.h"


/**
 * @todo refact
 */
void cpu_string_debug(PARAMS_DEFINE)
{
    /** @todo
    VALIDATE_NOT_DUALITY
    driver_tty_output(app, &app->cout.tty_debug, reg, GET_ANY_PARAM);
    */
}

/**
 * @startuml
 * (*) --> if "register column?" then
 *  -->[RY] "Read memory"
 *  --> "IO Write"
 * else
 *  -->[RZ] "IO Write"
 * endif
 * --> "Garbage Collector"
 * --> (*)
 * @enduml
 */
void cpu_string_output(struct app_3bc_s* const self)
{
    do {
        if (self->rc == TBC_RET_OK) {
            if (self->cpu.ry) {
                self->rc = TBC_RET_SYS_MEM_READ;
                break;
            } 
            self->cpu.ra = self->cpu.rz;
        }

        if (self->rc == TBC_RET_SYS_MEM_READ) {
            self->rc = TBC_RET_OK;
        }

        if (self->rc == TBC_RET_OK) {
            char* out = self->cache_l3.fixbuf.storage;
            static const size_t out_size = sizeof(self->cache_l3.fixbuf.storage);

            if (self->cpu.rx == STRC)
            {
                self->cache_l3.fixbuf.size = 1;
                self->cache_l3.fixbuf.storage[0] = self->cpu.ra;
            }
            else {
                /** @todo fix negative bit **/
                if (self->cpu.ra & 0b10000000) {
                    out += 1;
                    self->cpu.ra = (tbc_u8_t) -self->cpu.ra;
                    self->cache_l3.fixbuf.size += 1;
                    self->cache_l3.fixbuf.storage[0] = '-';
                }
                switch(self->cpu.rx)
                {
                    case STRO:
                        self->cache_l3.fixbuf.size += snprintf(out, out_size, "%o", (unsigned int) self->cpu.ra);
                        break;

                    case STRI:
                        self->cache_l3.fixbuf.size += cast_itos10(
                            self->cache_l3.fixbuf.storage,
                            &self->cpu.ra,
                            sizeof(self->cache_l3.fixbuf.storage),
                            13);
                        break;

                    case STRX:
                        self->cache_l3.fixbuf.size += snprintf(out, out_size, "%x", (unsigned int) self->cpu.ra);
                        break;                    
                }
            }
            self->cache_l2.tty = &(self->cout.tty_output);
            self->rc = TBC_RET_SYS_IO_WRITE;
            break;
        }

        if (self->rc == TBC_RET_SYS_IO_WRITE) {
            self->rc = TBC_RET_GC_LV3;
            break;
        }

        self->rc = TBC_RET_OK;
        break;
    }
    while (0);
}

void cpu_string_input(PARAMS_DEFINE)
{
    /** @todo
    VALIDATE_NOT_VALUES
    {
        data_3bc_t aux = driver_tty_input(app, &app->cin.tty_input, reg);
        driver_accumulator_set(app, aux);
        driver_memory_data_set(app, address, aux);
        driver_tty_output(app, &app->cout.tty_keylog, reg, aux);
    }*/
}

void cpu_string_input_silent(PARAMS_DEFINE)
{
    /** @todo
    VALIDATE_NOT_VALUES
    {
        data_3bc_t aux = driver_tty_input(app, &app->cin.tty_input, reg);
        driver_accumulator_set(app, aux);
        driver_memory_data_set(app, address, aux);
    }*/
}

void cpu_string_input_password(PARAMS_DEFINE)
{
    /** @todo
    VALIDATE_NOT_VALUES
    {
        data_3bc_t aux = driver_tty_input(app, &app->cin.tty_input, reg);
        driver_accumulator_set(app, aux);
        driver_memory_data_set(app, address, aux);
        driver_tty_output(app, &app->cout.tty_keylog, STRC, '*');
    }*/
}
