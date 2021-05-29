#include "3bc.h"

void cpu_input_stri(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    tape_aux_set(lang_driver_input(STRI, addres));
    tape_memory_data_set(addres, AUX);
    lang_driver_output(APP_3BC->tty_keylog, STRI, AUX);
}

void cpu_input_strc(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    tape_aux_set(lang_driver_input(STRC, addres));
    tape_memory_data_set(addres, AUX);
    lang_driver_output(APP_3BC->tty_keylog, STRC, AUX);    
}

void cpu_input_stro(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    tape_aux_set(lang_driver_input(STRO, addres));
    tape_memory_data_set(addres, AUX);
    lang_driver_output(APP_3BC->tty_keylog, STRO, AUX);
}

void cpu_input_strx(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    tape_aux_set(lang_driver_input(STRX, addres));
    tape_memory_data_set(addres, AUX);
    lang_driver_output(APP_3BC->tty_keylog, STRX, AUX);
}

void cpu_input_silent_stri(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    tape_aux_set(lang_driver_input(STRI, addres));
    tape_memory_data_set(addres, AUX);
}

void cpu_input_silent_strc(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    tape_aux_set(lang_driver_input(STRC, addres));
    tape_memory_data_set(addres, AUX);
}

void cpu_input_silent_stro(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    tape_aux_set(lang_driver_input(STRO, addres));
    tape_memory_data_set(addres, AUX);
}

void cpu_input_silent_strx(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    tape_aux_set(lang_driver_input(STRX, addres));
    tape_memory_data_set(addres, AUX);
}

void cpu_input_password_stri(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    tape_aux_set(lang_driver_input(STRI, addres));
    tape_memory_data_set(addres, AUX);
    lang_driver_output(APP_3BC->tty_keylog, STRC, '*');
}

void cpu_input_password_strc(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    tape_aux_set(lang_driver_input(STRC, addres));
    tape_memory_data_set(addres, AUX);
    lang_driver_output(APP_3BC->tty_keylog, STRC, '*');
}

void cpu_input_password_stro(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    tape_aux_set(lang_driver_input(STRO, addres));
    tape_memory_data_set(addres, AUX);
    lang_driver_output(APP_3BC->tty_keylog, STRC, '*');
}

void cpu_input_password_strx(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    tape_aux_set(lang_driver_input(STRX, addres));
    tape_memory_data_set(addres, AUX);
    lang_driver_output(APP_3BC->tty_keylog, STRC, '*');
}