#include "3bc.h"

void lang_line(reg_t reg, mem_t mem, val_t val)
{
    tape_program_resize();
    tape_program_line_add(reg, mem, val);
    tape_program_exe();
}