#define _3BC_SCU_FIX_2
#include "3bc.h"

app_3bc_t _instance;

/**
 * TODO: Dynamic array
 */
app_3bc_t ds_container_darray_new()
{
    _instance = (app_3bc_t) malloc(sizeof(struct app_3bc_s));
    _instance->id = 1;
    return _instance;
}

app_3bc_t ds_container_darray_get_one(app_3bc_id app)
{
    return _instance;
}
