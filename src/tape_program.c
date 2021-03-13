#define _3BC_REQUIRE_INSTRUCTIONS
#include "3bc.h"

compass_t target_label;
compass_t tape_last_cmode;
compass_t tape_last_label;
compass_t tape_last_line;
compass_t tape_current_line;

struct label_s {
    compass_t line;
    cch_t cpu_mode;
};

struct line_s {
    reg_t reg;
    mem_t adr;
    mem_t dta;
};

struct label_s* tape_labels;
struct line_s* tape_master;

/**
 * reset primitive state program
 */
void tape_program_init()
{
    /** reset counters **/
    tape_current_line = 0;
    tape_last_line = 0;
    target_label = 0;

    /** prevent wild pointers **/
    tape_labels = NULL;
    tape_master = NULL;
}

/**
 * record program memory,
 * similar to writing a line on the punch card.
 */
void tape_program_line_add(reg_t reg, mem_t mem, val_t val)
{
    /** register point label for jumps logical **/
    if (reg == NILL && mem == NILL && val != NILL) {
        tape_program_label_add(CELNE, val);
        val = 0;
    }

    /** remember last cpu change interpreted **/
    if (reg == MODE) {
        tape_last_cmode = val;
    }

    /** register program bytecode **/
    tape_master[CELNE].reg = reg;
    tape_master[CELNE].adr = mem;
    tape_master[CELNE].dta = val;
}

/**
 * Expand program memory,
 * provide more punch card lines.
 */
void tape_program_resize()
{
    /** expand program tape **/
    struct line_s* new_tape = (struct line_s*) realloc(tape_master, sizeof (struct line_s) * (tape_last_line += 1));

    /** was not possible expand program tape **/
    if (new_tape == NULL) {
        lang_driver_error(ERROR_TAPE_PROGRAM);
    }
    
    /** take program tape **/
    tape_master = new_tape;
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
    reg_f instruction = instructions(CMODE, tape_master[CLINE].reg);

    /**
     * Perform physical function
     */
    (instruction)(
        /** param for function: mem_t addres **/
        tape_master[CLINE].adr,
        /** param for function: val_t value **/
        tape_master[CLINE].dta
    );

    /** go next line **/
    tape_current_line += 1;
    return true;
}

/**
 * eject punch card program
 */
void tape_program_destroy()
{
    free(tape_labels);
    free(tape_master);
}

void tape_program_line_set(compass_t line)
{
    tape_current_line = line;
}

/**
 * current program line
 */
compass_t tape_program_line_get()
{
    return tape_current_line;
}

compass_t tape_program_line_end()
{
    return tape_last_line <= 0? 0: (tape_last_line - 1);
}

/**
 * mark point to logical jumps
 */
void tape_program_label_add(compass_t line, compass_t label)
{
    /** new label require asc order **/
    if (label < tape_last_label) {
        lang_driver_error(ERROR_INVALID_LABEL);
    }
   
    /** expand labels tape **/
    struct label_s* new_tape = (struct label_s*) realloc(tape_labels, sizeof (struct label_s) * (tape_last_label = label + 1));
    
    /** was not possible expand labels tape **/
    if (new_tape == NULL) {
        lang_driver_error(ERROR_TAPE_LABEL);
    }

    /** take labels tape **/
    tape_labels = new_tape;
    tape_labels[label].line = line;
    tape_labels[label].cpu_mode = tape_last_cmode;
}

/**
 * seek program label point
 */
void tape_program_target_label(compass_t label)
{
    target_label = label;
}

/**
 * check if there is tape program available
 */
bool tape_program_avaliable()
{
    /** jump target is solved **/
    if (target_label != NILL && target_label < tape_last_label) {
        tape_router_cpu_set(tape_labels[target_label].cpu_mode);
        tape_program_line_set(tape_labels[target_label].line);
        tape_program_target_label(0);
        return true;
    }
    /** waiting for label **/
    else if (target_label != NILL) {
        return false;
    }

    return tape_current_line < tape_last_line;
}