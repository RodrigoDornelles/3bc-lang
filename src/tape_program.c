#include "3bc.h"

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

void tape_program_line_add(reg_t reg, mem_t mem, val_t val)
{
    /** is a label **/
    if (reg == 0 && mem == 0 && val != 0) {
        tape_program_label_add(CLINE, val);
        val = 0;
    }
    tape_master[CELNE].reg = reg;
    tape_master[CELNE].adr = mem;
    tape_master[CELNE].dta = val;
}

void tape_program_resize()
{
    void* new_tape =  realloc(tape_master, sizeof (struct line_s) * (tape_last_line += 1));

    if (new_tape == NULL) {
        lang_driver_error(ERROR_TAPE_PROGRAM);
        return;
    }
    
    tape_master = new_tape;
}

RETURN_DEFINE tape_program_exe()
{
    /**
     *  call the register function
     * from within a two-dimensional array of pointers
     * FILE: register.h
     **/
    RETURN_DEFINE result = (*instructions[
        /** first index use current cpu channel **/
        CMODE
    ][  
        /** second index use function pointer register **/
        tape_master[CLINE].reg
    ])(
        /** param for function: mem_t addres **/
        tape_master[CLINE].adr,
        /** param for function: val_t value **/
        tape_master[CLINE].dta
    );

    tape_current_line += 1;
    return result;
}

void tape_program_destroy()
{
    free(tape_labels);
    free(tape_master);
}

void tape_program_line_set(compass_t line)
{
    tape_current_line = line;
}

compass_t tape_program_line_get()
{
    return tape_current_line;
}

compass_t tape_program_line_end()
{
    return tape_last_line <= 0? 0: (tape_last_line - 1);
}

void tape_program_label_add(compass_t line, compass_t label)
{
    if (label <= tape_last_label) {
        lang_driver_error(ERROR_INVALID_LABEL);
        return;
    }
   
    void* new_tape = realloc(tape_labels, sizeof (compass_t) * (tape_last_label = label + 1));
    
    if (new_tape == NULL) {
        lang_driver_error(ERROR_TAPE_LABEL);
        return;
    }

    tape_labels = new_tape;
    tape_labels[label].line = line;
    tape_labels[label].cpu_mode = CMODE;
}

void tape_program_target_label(compass_t label)
{
    if (label < tape_last_label) {
        tape_program_line_set(tape_labels[label].line);
        tape_router_cpu_set(tape_labels[label].cpu_mode);
        return;
    }
}

bool tape_program_avaliable()
{
    return tape_current_line < tape_last_line;
}