#define _3BC_SCU_FIX_2
#include "3bc.h"

app_3bc_t _instance;
app_3bc_t _instances[3] = {NULL};

/**
 * TODO: Dynamic array
 */
app_3bc_t ds_container_darray_new()
{
    _instance = (app_3bc_t) malloc(sizeof(struct app_3bc_s));
    memset(_instance, 0, sizeof(struct app_3bc_s));
    _instances[1] = _instance;
    _instance->id = 1;
    /** TODO: move somewhere **/ 
    _instance->memory.data_get = &ds_memory_llrbt_data_get;
    _instance->memory.conf_get = &ds_memory_llrbt_conf_get;
    _instance->memory.data_set = &ds_memory_llrbt_data_set;
    _instance->memory.conf_set = &ds_memory_llrbt_conf_set;
    return _instance;
}

app_3bc_t ds_container_darray_get_one(app_3bc_id app)
{
    return _instance;
}

app_3bc_t* ds_container_darray_get_all()
{
    return _instances;
}
