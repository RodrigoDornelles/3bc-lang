#include "3bc.h"

void cpu_debug_stri(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    AUX_USE_ANY_PARAM
    driver_io_output(APP_3BC->tty_debug, STRI, AUX);
}

void cpu_debug_strc(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    AUX_USE_ANY_PARAM
    driver_io_output(APP_3BC->tty_debug, STRC, AUX);
}

void cpu_debug_stro(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    AUX_USE_ANY_PARAM
    driver_io_output(APP_3BC->tty_debug, STRO, AUX);
}

void cpu_debug_strx(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    AUX_USE_ANY_PARAM
    driver_io_output(APP_3BC->tty_debug, STRX, AUX);
}
