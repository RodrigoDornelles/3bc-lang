#include "3bc.h"

void cpu_memory_free(PARAMS_DEFINE)
{
    REQUIRED_ADDRESS
    VALIDATE_NOT_VALUES
    tape_memory_free(addres);
}

void cpu_memory_aloc(PARAMS_DEFINE)
{
    REQUIRED_ADDRESS
    tape_memory_set(addres, value);
}

void cpu_memory_tcfg(PARAMS_DEFINE)
{
    REQUIRED_ADDRESS
    tape_memory_type_set(addres, value);
}

void cpu_memory_tmin(PARAMS_DEFINE)
{
    REQUIRED_ADDRESS
    tape_memory_value_min_set(addres, value);
}

void cpu_memory_tmax(PARAMS_DEFINE)
{
    REQUIRED_ADDRESS
    tape_memory_value_max_set(addres, value);
}

void cpu_memory_aux_free(PARAMS_DEFINE)
{
    VALIDATE_NOT_ADRESS
    VALIDATE_NOT_VALUES
    tape_aux_free();
}

void cpu_memory_aux_aloc(PARAMS_DEFINE)
{
    VALIDATE_NOT_ADRESS
    tape_aux_set(value);
}

void cpu_memory_aux_pull(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    tape_memory_set(addres, AUX);
}

void cpu_memory_aux_push(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    tape_aux_set(tape_memory_get(addres));
}

/**
 * invert values inner AUX & Memory
 */
void cpu_memory_aux_spin(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    val_t aux_old = AUX;
    tape_aux_set(tape_memory_get(addres));
    tape_memory_set(addres, aux_old);
}