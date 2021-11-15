#define _3BC_SCU_FIX_2
#include "3bc.h"

data_aux_3bc_t driver_accumulator_get()
{
    return APP_3BC->mem_aux;
}

void driver_accumulator_set(data_aux_3bc_t value)
{
    APP_3BC->mem_aux = value;
}