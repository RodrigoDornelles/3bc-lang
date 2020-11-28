#include "header.h"
#include "register.h"

val_t memory_aux;
val_t memory_cpu_mode;
val_t memory_safe[ (mem_t) MEMORY_SAFE_LIMIT ];

void cpu_memory_free(PARAMS_DEFINE)
{
    memory_safe[addres] = 0;
}

void cpu_memory_aloc(PARAMS_DEFINE)
{
    memory_safe[addres] = value;
}

void cpu_memory_copy(PARAMS_DEFINE)
{
    memory_safe[addres] = memory_safe[value];
}

void cpu_memory_size_get(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    if(addres) {
        memory_safe[addres] = MEMORY_SAFE_LIMIT;
    }

    memory_aux = memory_safe[addres];
}

void cpu_memory_size_set(PARAMS_DEFINE)
{

}

void cpu_memory_aux_free(PARAMS_DEFINE)
{
    VALIDATE_NOT_ADRESS
    VALIDATE_NOT_VALUES
    internal_memory_aux_free(NILL, NILL);
}

void cpu_memory_aux_aloc(PARAMS_DEFINE)
{
    VALIDATE_NOT_ADRESS
    internal_memory_aux_set(NILL, value);
}

void cpu_memory_aux_pull(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    cpu_memory_aloc(addres, memory_aux);
}

void cpu_memory_aux_push(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    internal_memory_aux_set(NILL, internal_memory_addres_get(addres, NILL));
}

/***********************************************************************/

val_t internal_memory_addres_get(PARAMS_DEFINE)
{
    return memory_safe[addres];
}

val_t internal_memory_aux_get(PARAMS_DEFINE)
{
    return memory_aux;
}

void internal_memory_aux_set(PARAMS_DEFINE)
{
    memory_aux = value;
}

void internal_memory_aux_free(PARAMS_DEFINE)
{
    memory_aux = 0;
}

val_t internal_memory_cpu_mode_get(PARAMS_DEFINE)
{
    return memory_cpu_mode;
}

void internal_memory_cpu_mode_set(PARAMS_DEFINE)
{
    memory_cpu_mode = value;
}