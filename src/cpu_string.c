#define _3BC_SCU_FIX_2
#include "3bc.h"

void cpu_string_debug(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    driver_tty_output(app->tty_debug, reg, GET_ANY_PARAM);
}

void cpu_string_output(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    driver_tty_output(app->tty_output, reg, GET_ANY_PARAM);
}

void cpu_string_input(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    {
        data_3bc_t aux = driver_tty_input(app->tty_input, reg);
        driver_accumulator_set(app, aux);
        driver_memory_data_set(app, address, aux);
        driver_tty_output(app->tty_keylog, reg, aux);
    }
}

void cpu_string_input_silent(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    {
        data_3bc_t aux = driver_tty_input(app->tty_input, reg);
        driver_accumulator_set(app, aux);
        driver_memory_data_set(app, address, aux);
    }
}

void cpu_string_input_password(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    {
        data_3bc_t aux = driver_tty_input(app->tty_input, reg);
        driver_accumulator_set(app, aux);
        driver_memory_data_set(app, address, aux);
        driver_tty_output(app->tty_keylog, STRC, '*');
    }
}
