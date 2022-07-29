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
 * Code refers reference labels for the code.
 *
 * DATASTRUCT:
 * Hash map.
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
 * mark point to logical jumps
 */
void ds_label_hash_insert(struct app_3bc_s* const app, label_3bc_t label)
{
    unsigned char hash;
    struct label_node_s* new_node;
    struct label_node_s* last_node;

    /** label already exists **/
    if (ds_label_hash_search(app, label) != NULL) {
        driver_program_error(app, ERROR_INVALID_LABEL);
    }

    new_node = (struct label_node_s*)malloc(sizeof(struct label_node_s));
    hash = label % LABEL_HASH_SIZE;

    /** was not possible expand labels **/
    if (new_node == NULL) {
        driver_program_error(app, ERROR_OUT_OF_MEMORY);
    }

    new_node->label = label;
    new_node->point = app->program.tail;
    new_node->cpumode = app->program.last_cpu;

    if (app->program.label_table[hash] == NULL) {
        app->program.label_table[hash] = new_node;
        new_node->next = NULL;
        return;
    }

    last_node = app->program.label_table[hash];
    for (; last_node->next != NULL; last_node = last_node->next)
        ;
    last_node->next = new_node;
}

/**
 * find label in hash tabel
 */
struct label_node_s* ds_label_hash_search(
    struct app_3bc_s* const app, label_3bc_t label)
{
    struct label_node_s* last_node
        = app->program.label_table[label % LABEL_HASH_SIZE];

    while (last_node != NULL) {
        if (last_node->label == label) {
            return last_node;
        }

        last_node = last_node->next;
    }

    return NULL;
}
