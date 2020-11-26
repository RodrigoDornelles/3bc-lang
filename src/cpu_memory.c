#include "header.h"
#include "register.h"

val_t memory_aux;
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

void cpu_memory_aux(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    if(addres) {
        cpu_memory_aux(NILL, memory_safe[addres]);
    }

    memory_aux = memory_safe[value];
}

val_t internal_memory_aux_get(PARAMS_DEFINE)
{
    return memory_aux;
}

void internal_memory_aux_set(PARAMS_DEFINE)
{
    memory_aux = value;
}