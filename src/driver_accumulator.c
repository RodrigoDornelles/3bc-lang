#define _3BC_SCU_FIX_2
#include "3bc.h"

data_aux_3bc_t driver_accumulator_get(struct app_3bc_s *const app)
{
    return app->mem_aux;
}

void driver_accumulator_set(struct app_3bc_s *const app, data_aux_3bc_t value)
{
    app->mem_aux = value;
}