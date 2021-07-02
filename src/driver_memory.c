#include "3bc.h"

void driver_memory_data_set(address_3bc_t address, data_3bc_t value)
{
    struct memory_node_s* node = tape_memory_llrbt_access(address);
    node->data = value;
    driver_memory_lineup(node);
}

void driver_memory_vmax_set(address_3bc_t address, data_3bc_t value)
{
    struct memory_node_s* node = tape_memory_llrbt_access(address);
    node->conf |= MEM_CONFIG_MAX_VALUE;
    node->vmax = value;
    driver_memory_lineup(node);
}

void driver_memory_vmin_set(address_3bc_t address, data_3bc_t value)
{
    struct memory_node_s* node = tape_memory_llrbt_access(address);
    node->conf |= MEM_CONFIG_MIN_VALUE;
    node->vmin = value;
    driver_memory_lineup(node);
}

void driver_memory_conf_set(address_3bc_t address, data_3bc_t value)
{
    struct memory_node_s* node = tape_memory_llrbt_access(address);
    node->conf = value;
    driver_memory_lineup(node);
}

data_3bc_t driver_memory_data_get(address_3bc_t address)
{
    struct memory_node_s* node = tape_memory_llrbt_access(address);
    return node->data;
}

data_3bc_t driver_memory_vmax_get(address_3bc_t address)
{
    struct memory_node_s* node = tape_memory_llrbt_access(address);
    return node->vmax;
}

data_3bc_t driver_memory_vmin_get(address_3bc_t address)
{
    struct memory_node_s* node = tape_memory_llrbt_access(address);
    return node->vmin;
}

data_3bc_t driver_memory_conf_get(address_3bc_t address)
{
    struct memory_node_s* node = tape_memory_llrbt_access(address);
    return node->conf;
}

/**
 * MACRO: POINTER 
 */
address_3bc_t driver_memory_pointer(address_3bc_t address)
{
    register address_3bc_t ptr = driver_memory_data_get(address);

    /**
     * JAVA PROGRAMMER BELIKE: 
     * omg i'm scared with null pointer!
     */
    if (ptr == NILL) {
        /** also apply to microsoft java devs (aka C#) */
        driver_program_error(ERROR_NULL_POINTER);
    }

    return ptr;
}


void driver_memory_lineup(struct memory_node_s* node)
{
    /** default configuration **/
    if (node->conf == 0) {
        return;
    }

    /** cache configuration **/
    bool conf_normalize = (MEM_CONFIG_NORMALIZE == (node->conf & MEM_CONFIG_NORMALIZE));
    bool conf_max_value = (MEM_CONFIG_MAX_VALUE == (node->conf & MEM_CONFIG_MAX_VALUE));
    bool conf_min_value = (MEM_CONFIG_MIN_VALUE == (node->conf & MEM_CONFIG_MIN_VALUE));
    bool conf_min_max = conf_max_value && conf_min_value;

    /** not allow normalize whitout clamp (limit max & min) **/
    if (conf_normalize && !conf_min_max) {
        driver_program_error(ERROR_INVALID_MEMORY_CONFIG);
    }

    /** verifiy valid value between max & min **/
    if (node->vmin > node->vmax && conf_min_max) {
        driver_program_error(ERROR_INVALID_MEMORY_CLAMP);
    }
    
    /** maximum without normalize **/
    if(node->data > node->vmax && conf_max_value && !conf_normalize) {
        node->data = node->vmax;
    }
    /** minimum without normalize **/
    else if (node->data < node->vmin && conf_min_value && !conf_normalize) {
        node->data = node->vmin;
    }
    /** custom underflow/overflow **/
    else if ((node->vmin > node->data || node->data > node->vmax) && conf_normalize) {
        node->data = ((node->data + node->vmin + 2) % (node->vmax - node->vmin + 1)) + node->vmin;
    }
}

void tape_memory_free(address_3bc_t address)
{
    /** clear cache level 0 **/
    if (APP_3BC->cache_l0 != NULL && APP_3BC->cache_l0->address == address) {
        APP_3BC->cache_l0 = NULL;
    }

    /** clear memory node **/
    APP_3BC->memory.root = tape_memory_llrbt_clear(address, APP_3BC->memory.root);
}