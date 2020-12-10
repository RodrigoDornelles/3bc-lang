#include "header.h"
#include "register.h"

void cpu_string_stri(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    AUX_USE_ANY_PARAM
    tape_output_serial_1(STRI, AUX);
}

void cpu_string_strc(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    AUX_USE_ANY_PARAM
    tape_output_serial_1(STRC, AUX);
}

void cpu_string_stro(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    AUX_USE_ANY_PARAM
    tape_output_serial_1(STRO, AUX);
}

void cpu_string_strx(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    AUX_USE_ANY_PARAM
    tape_output_serial_1(STRX, AUX);
}

void cpu_string_stru(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    AUX_USE_ANY_PARAM
    tape_output_serial_1(STRU, AUX);
}