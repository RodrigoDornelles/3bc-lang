#include "3bc.h"

data_3bc_t tape_aux_get()
{
    return APP_3BC->mem_aux;
}

void tape_aux_set(data_3bc_t value)
{
    APP_3BC->mem_aux = value;
}