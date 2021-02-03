#include "3bc.h"

RETURN_DEFINE cpu_null(PARAMS_DEFINE)
{
    return RETURN_OK;
}

RETURN_DEFINE cpu_mode(PARAMS_DEFINE)
{
    VALIDATE_NOT_ADRESS
    tape_router_cpu_set(value);
    return RETURN_OK;
}

RETURN_DEFINE cpu_not_mode(PARAMS_DEFINE)
{
    lang_driver_error(ERROR_CPU_ZERO);
    return RETURN_EXIT;
}

RETURN_DEFINE cpu_not_exist(PARAMS_DEFINE)
{
    lang_driver_error(ERROR_INVALID_REGISTER);
    return RETURN_OK;
}

RETURN_DEFINE cpu_mode_reserved(PARAMS_DEFINE)
{
    lang_driver_error(ERROR_CPU_RESERVED);
    return RETURN_EXIT;
}

RETURN_DEFINE cpu_mode_protected(PARAMS_DEFINE)
{
    lang_driver_error(ERROR_CPU_PROTECT);
    return RETURN_EXIT;
}