#include "header.h"
#include "register.h"

void cpu_memory_free(PARAMS_DEFINE)
{
    REQUIRED_ADDRESS
    VALIDATE_NOT_VALUES
    tape_memory_free(addres);
}

void cpu_memory_aloc(PARAMS_DEFINE)
{
    REQUIRED_ADDRESS
    REQUIRED_VALUE
    tape_memory_set(addres, value);
}

/**
 * @deprecated
 */
void cpu_memory_copy(PARAMS_DEFINE)
{

}

/**
 * @deprecated
 */
void cpu_memory_size_get(PARAMS_DEFINE)
{
    
}

/**
 * @deprecated
 */
void cpu_memory_size_set(PARAMS_DEFINE)
{

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