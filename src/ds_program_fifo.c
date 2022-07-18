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
 * Code refers to the program storage.
 *
 * DATASTRUCT:
 * Linked list, first in, first out.
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

/**
 * record program memory,
 * similar to writing a line on the punch card.
 */
void ds_program_fifo_line_add(struct app_3bc_s* const app, register_3bc_t reg,
    address_3bc_t mem, data_3bc_t val)
{
    /** register point label for jumps logical **/
    if (reg == NILL && mem == NILL && val != NILL) {
        ds_label_hash_insert(app, val);
        return;
    }

    /** remember last cpu change interpreted **/
    if (reg == MODE) {
        app->program.last_cpu = val;
    }

    /** register program bytecode **/
    ds_program_fifo_resize(app);
    app->program.tail->column.reg = reg;
    app->program.tail->column.adr = mem;
    app->program.tail->column.dta = val;
}

/**
 * Expand program memory,
 * provide more punch card lines.
 */
void ds_program_fifo_resize(struct app_3bc_s* const app)
{
    struct line_node_s* prev_line_node = app->program.tail;
    struct line_node_s* new_line_node
        = (struct line_node_s*)malloc(sizeof(struct line_node_s));

    /** was not possible expand program **/
    if (new_line_node == NULL) {
        driver_program_error(app, ERROR_OUT_OF_MEMORY);
    }

    /** first line program **/
    if (app->program.head == NULL) {
        app->program.head = new_line_node;
    }

    /** current line program **/
    if (app->program.curr == NULL) {
        app->program.curr = new_line_node;
    }

    /** link line program **/
    if (prev_line_node != NULL) {
        prev_line_node->next = new_line_node;
    }

    /** last line program **/
    app->program.tail = new_line_node;
    app->program.tail->next = NULL;
    app->program.tail->line = app->program.last_line;
}

/**
 * eject punch card program
 */
void ds_program_fifo_destroy(struct app_3bc_s* const app)
{
    struct line_node_s* node = app->program.head;
    struct line_node_s* prev;
    while (node != NULL) {
        prev = node;
        node = node->next;
        free(prev);
    }
}

/**
 * check if there is tape program available
 */
bool ds_program_fifo_avaliable(struct app_3bc_s* const app)
{
    /** waits for a label **/
    if (app->program.label_target != NILL) {
        struct label_node_s* label_node
            = ds_label_hash_search(app, app->program.label_target);

        /** cooming label **/
        if (label_node == NULL) {
            return false;
        }

        /** cooming next step after jump **/
        if (label_node->point->next == NULL) {
            return false;
        }

        /** jump to point **/
        driver_mode_set(app, label_node->cpumode);
        app->program.curr = label_node->point->next;
        app->program.label_target = NILL;
        return true;
    }

    /** end of program **/
    return app->program.curr != NULL;
}
