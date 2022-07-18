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
 * Code refers registers for the boolean logic unit.
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

void cpu_bitwise_not(PARAMS_DEFINE)
{
    VALIDATE_NOT_ADRESS
    VALIDATE_NOT_VALUES
    driver_accumulator_set(app, ~AUX);
}

void cpu_bitwise_and(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    driver_accumulator_set(app, AUX & GET_ANY_PARAM);
}

void cpu_bitwise_or(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    driver_accumulator_set(app, AUX | GET_ANY_PARAM);
}

void cpu_bitwise_xor(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    driver_accumulator_set(app, AUX ^ GET_ANY_PARAM);
}

void cpu_bitwise_nand(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    driver_accumulator_set(app, ~(AUX & GET_ANY_PARAM));
}

void cpu_bitwise_nor(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    driver_accumulator_set(app, ~(AUX | GET_ANY_PARAM));
}

void cpu_bitwise_xnor(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    driver_accumulator_set(app, ~(AUX ^ GET_ANY_PARAM));
}

void cpu_bitwise_left(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    VALIDATE_NOT_NEGATIVES
    driver_accumulator_set(app, AUX << GET_ANY_PARAM);
}

void cpu_bitwise_right(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    VALIDATE_NOT_NEGATIVES
    driver_accumulator_set(app, AUX >> GET_ANY_PARAM);
}

void cpu_bool_not(PARAMS_DEFINE)
{
    VALIDATE_NOT_ADRESS
    VALIDATE_NOT_VALUES
    driver_accumulator_set(app, !AUX);
}

void cpu_bool_and(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    VALIDATE_NOT_NEGATIVES
    driver_accumulator_set(app, AUX && GET_ANY_PARAM);
}

void cpu_bool_or(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    VALIDATE_NOT_NEGATIVES
    driver_accumulator_set(app, AUX || GET_ANY_PARAM);
}

void cpu_bool_xor(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    VALIDATE_NOT_NEGATIVES
    driver_accumulator_set(app, (!!AUX) ^ (!!GET_ANY_PARAM));
}

void cpu_bool_nand(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    VALIDATE_NOT_NEGATIVES
    driver_accumulator_set(app, !(AUX && GET_ANY_PARAM));
}

void cpu_bool_nor(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    VALIDATE_NOT_NEGATIVES
    driver_accumulator_set(app, !(AUX || GET_ANY_PARAM));
}

void cpu_bool_xnor(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    VALIDATE_NOT_NEGATIVES
    driver_accumulator_set(app, !((!!AUX) ^ (!!GET_ANY_PARAM)));
}
