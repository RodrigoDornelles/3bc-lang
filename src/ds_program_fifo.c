#define _3BC_SCU_FIX_2
#include "3bc.h"

/**
 * record program memory,
 * similar to writing a line on the punch card.
 */
void ds_program_fifo_line_add(app_3bc_t app, register_3bc_t reg, address_3bc_t mem, data_3bc_t val)
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
void ds_program_fifo_resize(app_3bc_t app)
{
    struct line_node_s* prev_line_node = app->program.tail;
    struct line_node_s* new_line_node = (struct line_node_s*) malloc(sizeof (struct line_node_s));

    /** was not possible expand program **/
    if (new_line_node == NULL) {
        driver_program_error(app, ERROR_OUT_OF_MEMORY);
    }
    
    /** first line program **/
    if (app->program.head == NULL) {
        app->program.head = new_line_node;
    }

    /** current line program **/
    if (app->program.curr == NULL){
        app->program.curr = new_line_node;
    }

    /** link line program **/
    if (prev_line_node != NULL ) {
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
void ds_program_fifo_destroy(app_3bc_t app)
{
    struct line_node_s* node = app->program.head;
    struct line_node_s* prev;
    while (node != NULL)
    {
        prev = node;
        node = node->next; 
        free(prev);
    }
}

/**
 * check if there is tape program available
 */
bool ds_program_fifo_avaliable(app_3bc_t app)
{
    /** waits for a label **/
    if (app->program.label_target != NILL) {
        struct label_node_s* label_node = ds_label_hash_search(app, app->program.label_target);

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
