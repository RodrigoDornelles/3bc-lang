#include "3bc.h"

void cpu_string_strb(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    driver_io_output(APP_3BC->tty_output, STRB, GET_ANY_PARAM);
}

void cpu_string_stri(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    driver_io_output(APP_3BC->tty_output, STRI, GET_ANY_PARAM);
}

void cpu_string_strc(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    driver_io_output(APP_3BC->tty_output, STRC, GET_ANY_PARAM);
}

void cpu_string_stro(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    driver_io_output(APP_3BC->tty_output, STRO, GET_ANY_PARAM);
}

void cpu_string_strx(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    driver_io_output(APP_3BC->tty_output, STRX, GET_ANY_PARAM);
}

