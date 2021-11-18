#define _3BC_SCU_FIX_2
#include "3bc.h"

data_aux_3bc_t driver_accumulator_get(app_3bc_t app)
{
    return app->mem_aux;
}

void driver_accumulator_set(app_3bc_t app, data_aux_3bc_t value)
{
    app->mem_aux = value;
}