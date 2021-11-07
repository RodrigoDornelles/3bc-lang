#include "3bc.h"

void driver_memory_data_set(address_3bc_t address, data_3bc_t value)
{
    memory_conf_t conf = APP_3BC->memory.conf_get(address);

    driver_gpio_output(conf, address, value);
    
    APP_3BC->memory.data_set(address, value);
}

void driver_memory_conf_set(address_3bc_t address, data_3bc_t conf)
{
    data_3bc_t value = APP_3BC->memory.data_get(address);

    driver_memory_validate(conf);
    driver_gpio_setup(conf, address);
    driver_gpio_output(conf, address, value);
    value = driver_gpio_input(conf, address, value);

    APP_3BC->memory.conf_set(address, conf);
    APP_3BC->memory.data_set(address, value);
}

data_3bc_t driver_memory_data_get(address_3bc_t address)
{
    data_3bc_t value = APP_3BC->memory.data_get(address);
    memory_conf_t conf = APP_3BC->memory.conf_get(address);

    /** read gpios if necessary **/
    value = driver_gpio_input(conf, address, value);

    return value;
}

optional_inline data_3bc_t driver_memory_conf_get(address_3bc_t address)
{
    return APP_3BC->memory.conf_get(address);
}

/**
 * MACRO: POINTER 
 */
address_3bc_t driver_memory_pointer(address_3bc_t address)
{
    register address_3bc_t ptr = driver_memory_data_get(address);

    /**
     * JOKE:
     * 
     * JAVA PROGRAMMER BE LIKE
     * omg i'm scared with null pointer!
     */
    if (ptr == NILL) {
        /** also apply to microsoft java devs (aka C#) */
        driver_program_error(ERROR_NULL_POINTER);
    }

    return ptr;
}

void driver_memory_validate(memory_conf_t conf)
{
    /** optimize **/
    if (conf == 0) {
        return;
    }
    /** not allow pullup and analogic some times **/
    if (BITFIELD_HAS(conf, MEM_CONFIG_GPIO_ANAL | MEM_CONFIG_GPIO_PULL)) {
        driver_program_error(ERROR_INVALID_MEMORY_CONFIG);
    }
    /** not allow pullup and output some times **/
    if (BITFIELD_HAS(conf, MEM_CONFIG_GPIO_SEND | MEM_CONFIG_GPIO_PULL)) {
        driver_program_error(ERROR_INVALID_MEMORY_CONFIG);
    }
    /** not allow input and output some times **/
    if (BITFIELD_HAS(conf, MEM_CONFIG_GPIO_SEND | MEM_CONFIG_GPIO_READ)) {
        driver_program_error(ERROR_INVALID_MEMORY_CONFIG);
    }
    /** analogic required input or output **/
    if (BITFIELD_HAS(conf, MEM_CONFIG_GPIO_ANAL) && !(BITFIELD_HAS(conf, MEM_CONFIG_GPIO_READ) || BITFIELD_HAS(conf, MEM_CONFIG_GPIO_SEND))) {
        driver_program_error(ERROR_INVALID_MEMORY_CONFIG);
    }
}

void driver_memory_free(address_3bc_t address)
{
    /** clear cache level 0 **/
    if (APP_3BC->cache_l0 != NULL && APP_3BC->cache_l0->address == address) {
        APP_3BC->cache_l0 = NULL;
    }

    /** clear memory node **/
    APP_3BC->memory.root = ds_memory_llrbt_clear(address, APP_3BC->memory.root);
}