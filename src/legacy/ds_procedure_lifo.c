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
 * Code refers stacking of called procedures.
 *
 * DATASTRUCT:
 * Linked list, last in, first out.
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

void ds_procedure_lifo_push(struct app_3bc_s* const app)
{
    struct procedure_3bc_s* procedure
        = (struct procedure_3bc_s*)malloc(sizeof(struct procedure_3bc_s));

    if (procedure == NULL) {
        driver_program_error(app, ERROR_OUT_OF_MEMORY);
    }

    procedure->prev = app->program.stack;
    procedure->remember = app->program.curr;

    app->program.stack = procedure;
}

struct line_node_s* ds_procedure_lifo_pop(struct app_3bc_s* const app)
{
    struct line_node_s* line_node;
    struct procedure_3bc_s* procedure;

    if (app->program.stack == NULL) {
        driver_program_error(app, ERROR_INVALID_RETURN);
    }

    procedure = app->program.stack->prev;
    line_node = app->program.stack->remember;
    free(app->program.stack);

    app->program.stack = procedure;

    return line_node;
}
