#define _3BC_SCU_FIX_2
#include "3bc.h"

/**
 * mark point to logical jumps
 */
void ds_label_hash_insert(app_3bc_t app, label_3bc_t label)
{ 
    unsigned char hash;
    struct label_node_s* new_node; 
    struct label_node_s* last_node; 

    /** label already exists **/
    if (ds_label_hash_search(app, label) != NULL) {
        driver_program_error(app, ERROR_INVALID_LABEL);
    }

    new_node = (struct label_node_s*) malloc(sizeof(struct label_node_s));
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
    for (;last_node->next != NULL; last_node = last_node->next);
    last_node->next = new_node;
}

/**
 * find label in hash tabel
 */
struct label_node_s* ds_label_hash_search(app_3bc_t app, label_3bc_t label)
{
    struct label_node_s* last_node = app->program.label_table[label % LABEL_HASH_SIZE];
    
    while (last_node != NULL) {
        if (last_node->label == label) {
            return last_node;
        }

        last_node = last_node->next;
    }

    return NULL;
}
