#include "3bc.h"

RETURN_DEFINE cpu_input_stri(PARAMS_DEFINE)
{
    value = getch_parser("%i");
    tape_aux_set(value);
    tape_memory_set(addres, AUX);
    lang_driver_output_1(STRI, AUX);
    return RETURN_OK;
}

RETURN_DEFINE cpu_input_strc(PARAMS_DEFINE)
{
    value = getch();
    tape_aux_set(value);
    tape_memory_set(addres, AUX);
    lang_driver_output_1(STRC, AUX);
    return RETURN_OK;
}

RETURN_DEFINE cpu_input_stro(PARAMS_DEFINE)
{
    value = getch_parser("%o");
    tape_aux_set(value);
    tape_memory_set(addres, AUX);
    lang_driver_output_1(STRI, AUX);
    return RETURN_OK;
}

RETURN_DEFINE cpu_input_strx(PARAMS_DEFINE)
{
    value = getch_parser("%x");
    tape_aux_set(value);
    tape_memory_set(addres, AUX);
    lang_driver_output_1(STRI, AUX);
    return RETURN_OK;
}

RETURN_DEFINE cpu_input_silent_stri(PARAMS_DEFINE)
{
    value = getch_parser("%i");
    tape_aux_set(value);
    tape_memory_set(addres, AUX);
    return RETURN_OK;
}

RETURN_DEFINE cpu_input_silent_strc(PARAMS_DEFINE)
{
    value = getch();
    tape_aux_set(value);
    tape_memory_set(addres, AUX);
    return RETURN_OK;
}

RETURN_DEFINE cpu_input_silent_stro(PARAMS_DEFINE)
{
    value = getch_parser("%o");
    tape_aux_set(value);
    tape_memory_set(addres, AUX);
    return RETURN_OK;
}

RETURN_DEFINE cpu_input_silent_strx(PARAMS_DEFINE)
{
    value = getch_parser("%x");
    tape_aux_set(value);
    tape_memory_set(addres, AUX);
    return RETURN_OK;
}

RETURN_DEFINE cpu_input_password_stri(PARAMS_DEFINE)
{
    value = getch_parser("%i");
    tape_aux_set(value);
    tape_memory_set(addres, AUX);
    lang_driver_output_1(STRC, '*');
    return RETURN_OK;
}

RETURN_DEFINE cpu_input_password_strc(PARAMS_DEFINE)
{
    value = getch();
    tape_aux_set(value);
    tape_memory_set(addres, AUX);
    lang_driver_output_1(STRC, '*');
    return RETURN_OK;
}

RETURN_DEFINE cpu_input_password_stro(PARAMS_DEFINE)
{
    value = getch_parser("%o");
    tape_aux_set(value);
    tape_memory_set(addres, AUX);
    lang_driver_output_1(STRC, '*');
    return RETURN_OK;
}

RETURN_DEFINE cpu_input_password_strx(PARAMS_DEFINE)
{
    value = getch_parser("%x");
    tape_aux_set(value);
    tape_memory_set(addres, AUX);
    lang_driver_output_1(STRC, '*');
    return RETURN_OK;
}