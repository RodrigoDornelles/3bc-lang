#include "3bc.h"

static data_3bc_t memory_aux;

data_3bc_t tape_aux_get()
{
    return memory_aux;
}

void tape_aux_set(data_3bc_t value)
{
    memory_aux = value;
}

void tape_aux_free()
{
    memory_aux = 0;
}