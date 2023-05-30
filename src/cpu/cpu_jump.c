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
 * Code refers registers for conditional jumps.
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

void cpu_jump_goto(PARAMS_DEFINE)
{
    /** @todo rewrite 
    REQUIRED_VALUE
    VALIDATE_NOT_ADRESS
    app->program.label_target = value;
    */
}

void cpu_jump_fgto(PARAMS_DEFINE)
{
    /** @todo rewrite 
    REQUIRED_VALUE
    VALIDATE_NOT_ADRESS
    if (AUX != 0) {
        app->program.label_target = value;
    }
    */
}

void cpu_jump_zgto(PARAMS_DEFINE)
{
    /** @todo rewrite 
    REQUIRED_VALUE
    VALIDATE_NOT_ADRESS
    if (AUX == 0) {
        app->program.label_target = value;
    }
    */
}

void cpu_jump_pgto(PARAMS_DEFINE)
{
    /** @todo rewrite 
    REQUIRED_VALUE
    VALIDATE_NOT_ADRESS
    if (0 < AUX) {
        app->program.label_target = value;
    }
    */
}

void cpu_jump_ngto(PARAMS_DEFINE)
{
    /** @todo rewrite 
    REQUIRED_VALUE
    VALIDATE_NOT_ADRESS
    if (0 > AUX) {
        app->program.label_target = value;
    }
    */
}