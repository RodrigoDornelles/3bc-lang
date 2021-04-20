#include "3bc.h"

void cpu_jump_goto(PARAMS_DEFINE)
{
    REQUIRED_VALUE
    VALIDATE_NOT_ADRESS
    tape_program_target_label(value);
}

void cpu_jump_fgto(PARAMS_DEFINE)
{
    REQUIRED_VALUE
    VALIDATE_NOT_ADRESS
    if (AUX != 0) {
        tape_program_target_label(value);
    }
}


void cpu_jump_zgto(PARAMS_DEFINE)
{
    REQUIRED_VALUE
    VALIDATE_NOT_ADRESS
    if (AUX == 0) {
        tape_program_target_label(value);
    }
}

void cpu_jump_pgto(PARAMS_DEFINE)
{
    REQUIRED_VALUE
    VALIDATE_NOT_ADRESS
    if ( 0 < (signed int) (AUX) ) {
        tape_program_target_label(value);
    }
}

void cpu_jump_ngto(PARAMS_DEFINE)
{
    REQUIRED_VALUE
    VALIDATE_NOT_ADRESS
    if ( 0 > (signed int) (AUX) ) {
        tape_program_target_label(value);
    }
}