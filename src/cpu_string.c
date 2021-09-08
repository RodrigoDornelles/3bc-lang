#include "3bc.h"

void cpu_string_strb(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    AUX_USE_ANY_PARAM
    driver_io_output(APP_3BC->tty_output, STRB, AUX);
}

void cpu_string_stri(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    AUX_USE_ANY_PARAM
    driver_io_output(APP_3BC->tty_output, STRI, AUX);
}

void cpu_string_strc(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    AUX_USE_ANY_PARAM
    driver_io_output(APP_3BC->tty_output, STRC, AUX);
}

void cpu_string_stro(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    AUX_USE_ANY_PARAM
    driver_io_output(APP_3BC->tty_output, STRO, AUX);
}

void cpu_string_strx(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    AUX_USE_ANY_PARAM
    driver_io_output(APP_3BC->tty_output, STRX, AUX);
}

