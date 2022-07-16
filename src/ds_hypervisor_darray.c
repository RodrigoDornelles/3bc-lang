#define TBC_SOURCE_ENTRY
#include "3bc.h"

static app_3bc_id machines_count;
static struct app_3bc_s** machines_array;

/**
 * Expand number of virtual machines
 *
 * DATASTRUCT: Dynamic array
 */
struct app_3bc_s* const ds_hypervisor_darray_new()
{
    struct app_3bc_s* new_vm
        = (struct app_3bc_s* const)malloc(sizeof(struct app_3bc_s));

    /** Suceful craete new machine **/
    if (new_vm != NULL) {
        struct app_3bc_s** new_array = (struct app_3bc_s**)realloc(
            machines_array, sizeof(struct app_3bc_s*) * (++machines_count));

        /** not possible expand array **/
        if (new_array == NULL) {
            machines_count -= 1;
            free(new_vm);
            return NULL;
        }

        /** setup hypervisor **/
        machines_array = new_array;
        machines_array[machines_count - 1] = new_vm;
        memset(new_vm, 0, sizeof(struct app_3bc_s));

        /** basic setup machine **/
        new_vm->id = machines_count - 1;
        new_vm->memory.data_get = &ds_memory_llrbt_data_get;
        new_vm->memory.conf_get = &ds_memory_llrbt_conf_get;
        new_vm->memory.data_set = &ds_memory_llrbt_data_set;
        new_vm->memory.conf_set = &ds_memory_llrbt_conf_set;
        return new_vm;
    }

    return NULL;
}

/**
 * RETURN: virutal machine by id
 */
struct app_3bc_s* const ds_hypervisor_darray_get_one(app_3bc_id app)
{
    return machines_array[app];
}

/**
 *  RETURN: array of virtual machines
 */
struct app_3bc_s** ds_hypervisor_darray_get_all()
{
    return machines_array;
}
