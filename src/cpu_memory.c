#include "3bc.h"

RETURN_DEFINE cpu_memory_free(PARAMS_DEFINE)
{
    REQUIRED_ADDRESS
    VALIDATE_NOT_VALUES
    tape_memory_free(addres);
    return RETURN_OK;
}

RETURN_DEFINE cpu_memory_aloc(PARAMS_DEFINE)
{
    REQUIRED_ADDRESS
    tape_memory_set(addres, value);
    return RETURN_OK;
}

RETURN_DEFINE cpu_memory_tcfg(PARAMS_DEFINE)
{
    REQUIRED_ADDRESS
    tape_memory_type_set(addres, value);
    return RETURN_OK;
}

RETURN_DEFINE cpu_memory_tmin(PARAMS_DEFINE)
{
    REQUIRED_ADDRESS
    tape_memory_value_min(addres, value);
    return RETURN_OK;
}

RETURN_DEFINE cpu_memory_tmax(PARAMS_DEFINE)
{
    REQUIRED_ADDRESS
    tape_memory_value_max(addres, value);
    return RETURN_OK;
}

RETURN_DEFINE cpu_memory_aux_free(PARAMS_DEFINE)
{
    VALIDATE_NOT_ADRESS
    VALIDATE_NOT_VALUES
    tape_aux_free();
    return RETURN_OK;
}

RETURN_DEFINE cpu_memory_aux_aloc(PARAMS_DEFINE)
{
    VALIDATE_NOT_ADRESS
    tape_aux_set(value);
    return RETURN_OK;
}

RETURN_DEFINE cpu_memory_aux_pull(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    tape_memory_set(addres, AUX);
    return RETURN_OK;
}

RETURN_DEFINE cpu_memory_aux_push(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    tape_aux_set(tape_memory_get(addres));
    return RETURN_OK;
}