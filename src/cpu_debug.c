#define _3BC_SCU_FIX_2
#include "3bc.h"

void cpu_debug_strb(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    AUX_USE_ANY_PARAM
    driver_tty_output(APP_3BC->tty_debug, STRB, AUX);
}

void cpu_debug_stri(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    AUX_USE_ANY_PARAM
    driver_tty_output(APP_3BC->tty_debug, STRI, AUX);
}

void cpu_debug_strc(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    AUX_USE_ANY_PARAM
    driver_tty_output(APP_3BC->tty_debug, STRC, AUX);
}

void cpu_debug_stro(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    AUX_USE_ANY_PARAM
    driver_tty_output(APP_3BC->tty_debug, STRO, AUX);
}

void cpu_debug_strx(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    AUX_USE_ANY_PARAM
    driver_tty_output(APP_3BC->tty_debug, STRX, AUX);
}
