#include "header.h"
#include "register.h"

compass_t tape_last_line;
compass_t tape_current_line;

struct line_s* tape_master;

void tape_program_add(reg_t reg, mem_t mem, val_t val)
{
    tape_master[CELNE].reg = reg;
    tape_master[CELNE].adr = mem;
    tape_master[CELNE].dta = val;
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
        tape_master[CLINE].reg
    ])(
        // param for function: mem_t addres
        tape_master[CLINE].adr,
        // param for function: val_t value
        tape_master[CLINE].dta
    );

    tape_current_line += 1;
}

void tape_program_destroy()
{
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