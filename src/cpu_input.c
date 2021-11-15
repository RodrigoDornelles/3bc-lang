#define _3BC_SCU_FIX_2
#include "3bc.h"

void cpu_input_strb(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    driver_accumulator_set(driver_tty_input(STRB, address));
    driver_memory_data_set(address, AUX);
    driver_tty_output(APP_3BC->tty_keylog, STRB, AUX);
}

void cpu_input_stri(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    driver_accumulator_set(driver_tty_input(STRI, address));
    driver_memory_data_set(address, AUX);
    driver_tty_output(APP_3BC->tty_keylog, STRI, AUX);
}

void cpu_input_strc(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    driver_accumulator_set(driver_tty_input(STRC, address));
    driver_memory_data_set(address, AUX);
    driver_tty_output(APP_3BC->tty_keylog, STRC, AUX);    
}

void cpu_input_stro(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    driver_accumulator_set(driver_tty_input(STRO, address));
    driver_memory_data_set(address, AUX);
    driver_tty_output(APP_3BC->tty_keylog, STRO, AUX);
}

void cpu_input_strx(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    driver_accumulator_set(driver_tty_input(STRX, address));
    driver_memory_data_set(address, AUX);
    driver_tty_output(APP_3BC->tty_keylog, STRX, AUX);
}

void cpu_input_silent_strb(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    driver_accumulator_set(driver_tty_input(STRB, address));
    driver_memory_data_set(address, AUX);
}

void cpu_input_silent_stri(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    driver_accumulator_set(driver_tty_input(STRI, address));
    driver_memory_data_set(address, AUX);
}

void cpu_input_silent_strc(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    driver_accumulator_set(driver_tty_input(STRC, address));
    driver_memory_data_set(address, AUX);
}

void cpu_input_silent_stro(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    driver_accumulator_set(driver_tty_input(STRO, address));
    driver_memory_data_set(address, AUX);
}

void cpu_input_silent_strx(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    driver_accumulator_set(driver_tty_input(STRX, address));
    driver_memory_data_set(address, AUX);
}

void cpu_input_password_strb(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    driver_accumulator_set(driver_tty_input(STRB, address));
    driver_memory_data_set(address, AUX);
    driver_tty_output(APP_3BC->tty_keylog, STRC, '*');
}

void cpu_input_password_stri(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    driver_accumulator_set(driver_tty_input(STRI, address));
    driver_memory_data_set(address, AUX);
    driver_tty_output(APP_3BC->tty_keylog, STRC, '*');
}

void cpu_input_password_strc(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    driver_accumulator_set(driver_tty_input(STRC, address));
    driver_memory_data_set(address, AUX);
    driver_tty_output(APP_3BC->tty_keylog, STRC, '*');
}

void cpu_input_password_stro(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    driver_accumulator_set(driver_tty_input(STRO, address));
    driver_memory_data_set(address, AUX);
    driver_tty_output(APP_3BC->tty_keylog, STRC, '*');
}

void cpu_input_password_strx(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    driver_accumulator_set(driver_tty_input(STRX, address));
    driver_memory_data_set(address, AUX);
    driver_tty_output(APP_3BC->tty_keylog, STRC, '*');
}