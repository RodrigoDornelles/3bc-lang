#include "header.h"
#include "register.h"

compass_t tape_last_line;
compass_t tape_current_line;

struct line_s* tape_master;

void tape_program_add(reg_t reg, mem_t mem, val_t val)
{
    tape_master[tape_last_line].reg = reg;
    tape_master[tape_last_line].adr = mem;
    tape_master[tape_last_line].dta = val;
}

void tape_program_resize()
{
    // expand program tape size
    tape_last_line += 1;
    tape_master = realloc(tape_master, sizeof (struct line_s) * (tape_last_line));
}

void tape_program_exe()
{
    // call the register function
    // from within a two-dimensional array of pointers
    // FILE: register.h
    (*instructions[
        // first index use current cpu channel
        CMODE
    ][  
        // second index use function pointer register
        tape_master[tape_current_line].reg
    ])(
        // param for function: mem_t addres
        tape_master[tape_current_line].adr,
        // param for function: val_t value
        tape_master[tape_current_line].dta
    );

    tape_current_line += 1;
}