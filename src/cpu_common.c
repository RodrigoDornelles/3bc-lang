#include "3bc.h"

void cpu_null(PARAMS_DEFINE)
{
}

void cpu_mode(PARAMS_DEFINE)
{
    VALIDATE_NOT_ADRESS
    tape_router_cpu_set(value);
}

void cpu_not_mode(PARAMS_DEFINE)
{
    lang_driver_error(ERROR_CPU_ZERO);
}

void cpu_not_exist(PARAMS_DEFINE)
{
    lang_driver_error(ERROR_INVALID_REGISTER);
}

void cpu_mode_reserved(PARAMS_DEFINE)
{
    lang_driver_error(ERROR_CPU_RESERVED);
}