#define _3BC_REQUIRE_INSTRUCTIONS
#include "3bc.h"

/**
 * record program memory,
 * similar to writing a line on the punch card.
 */
void tape_program_line_add(register_3bc_t reg, address_3bc_t mem, data_3bc_t val)
{
    /** register point label for jumps logical **/
    if (reg == NILL && mem == NILL && val != NILL) {
        tape_program_label_insert(val, APP_3BC->program.last_cpu, APP_3BC->program.tail);
        return;
    }

    /** remember last cpu change interpreted **/
    if (reg == MODE) {
        APP_3BC->program.last_cpu = val;
    }

    /** register program bytecode **/
    tape_program_resize();
    APP_3BC->program.tail->column.reg = reg;
    APP_3BC->program.tail->column.adr = mem;
    APP_3BC->program.tail->column.dta = val;
}

/**
 * Expand program memory,
 * provide more punch card lines.
 */
void tape_program_resize()
{
    struct line_node_s* prev_line_node = APP_3BC->program.tail;
    struct line_node_s* new_line_node = (struct line_node_s*) malloc(sizeof (struct line_node_s));

    /** was not possible expand program **/
    if (new_line_node == NULL) {
        lang_driver_error(ERROR_TAPE_PROGRAM);
    }
    
    /** first line program **/
    if (APP_3BC->program.head == NULL) {
        APP_3BC->program.head = new_line_node;
    }

    /** current line program **/
    if (APP_3BC->program.curr == NULL){
        APP_3BC->program.curr = new_line_node;
    }

    /** link line program **/
    if (prev_line_node != NULL ) {
        prev_line_node->next = new_line_node;
    }
    
    /** last line program **/
    APP_3BC->program.tail = new_line_node;
    APP_3BC->program.tail->next = NULL;
    APP_3BC->program.tail->line = APP_3BC->program.last_line;
}

/**
 * run processor instructions,
 * this is a core of virtual machine
 */
bool tape_program_exe()
{
    /**
     * request function pointer to machine instruction
     * FILE: 3bc_register.h
     */
    reg_f instruction = instructions(APP_3BC->cpu_mode, APP_3BC->program.curr->column.reg);

    /**
     * Perform physical function
     */
    (instruction)(
        /** param for function: address_3bc_t addres **/
        APP_3BC->program.curr->column.adr,
        /** param for function: data_3bc_t value **/
        APP_3BC->program.curr->column.dta
    );

    /** go next line **/
    APP_3BC->program.curr = APP_3BC->program.curr->next;
    return true;
}

/**
 * eject punch card program
 */
void tape_program_destroy()
{
    struct line_node_s* node = APP_3BC->program.head;
    struct line_node_s* prev;
    for (;node != NULL; prev = node, node = node->next, free(prev));
}

/**
 * mark point to logical jumps
 */
void tape_program_label_insert(label_3bc_t label, cpumode_3bc_t cpumode, struct line_node_s* line)
{
    /** label already exists **/
    if (tape_program_label_search(label) != NULL) {
        lang_driver_error(ERROR_INVALID_LABEL);
    }

    struct label_node_s* new_node = (struct label_node_s*) malloc(sizeof(struct label_node_s));
    unsigned char hash = label % LABEL_HASH_SIZE;

    /** was not possible expand labels **/
    if (new_node == NULL) {
        lang_driver_error(ERROR_TAPE_LABEL);
    }

    new_node->label = label;
    new_node->point = APP_3BC->program.tail;
    new_node->cpumode = APP_3BC->program.last_cpu;

    if (APP_3BC->program.label_table[hash] == NULL) {
        APP_3BC->program.label_table[hash] = new_node;
        new_node->next = NULL;
        return;
    }

    struct label_node_s* last_node = APP_3BC->program.label_table[hash];
    for (;last_node->next != NULL; last_node = last_node->next);
    last_node->next = new_node;
}

/**
 * find label in hash tabel
 */
struct label_node_s* tape_program_label_search(label_3bc_t label)
{
    struct label_node_s* last_node = APP_3BC->program.label_table[label % LABEL_HASH_SIZE];
    
    while (last_node != NULL) {
        if (last_node->label == label) {
            return last_node;
        }

        last_node = last_node->next;
    }

    return NULL;
}


/**
 * check if there is tape program available
 */
bool tape_program_avaliable()
{
    /** waits for a label **/
    if (APP_3BC->program.label_target != NILL) {
        struct label_node_s* label_node = tape_program_label_search(APP_3BC->program.label_target);

        /** cooming label **/
        if (label_node == NULL) {
            return false;
        }

        /** cooming next step after jump **/
        if (label_node->point->next == NULL) {
            return false;
        }
    
        /** jump to point **/
        tape_router_cpu_set(label_node->cpumode);
        APP_3BC->program.curr = label_node->point->next;
        APP_3BC->program.label_target = NILL;
        return true;
    }

    /** end of program **/
    return APP_3BC->program.curr != NULL;
}
