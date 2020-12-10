#include "header.h"

val_t memory_safe[ (mem_t) MEMORY_SAFE_LIMIT ];

val_t tape_memory_get(mem_t addres)
{
    return memory_safe[addres];
}

void tape_memory_set(mem_t addres, val_t value)
{
    memory_safe[addres] = value;
}

void tape_memory_free(mem_t addres)
{
    memory_safe[addres] = 0;
}