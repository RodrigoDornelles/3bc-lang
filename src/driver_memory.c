#define _3BC_SCU_FIX_2
#include "3bc.h"

void driver_memory_data_set(app_3bc_t app, address_3bc_t address, data_3bc_t value)
{
    memory_conf_t conf = app->memory.conf_get(app->id, address);

    driver_gpio_output(app, conf, address, value);
    
    app->memory.data_set(app->id, address, value);
}

void driver_memory_conf_set(app_3bc_t app, address_3bc_t address, data_3bc_t conf)
{
    data_3bc_t value = app->memory.data_get(app->id, address);

    driver_memory_validate(app, conf);
    driver_gpio_setup(app, conf, address);
    driver_gpio_output(app, conf, address, value);
    value = driver_gpio_input(app, conf, address, value);

    app->memory.conf_set(app->id, address, conf);
    app->memory.data_set(app->id, address, value);
}

data_3bc_t driver_memory_data_get(app_3bc_t app, address_3bc_t address)
{
    data_3bc_t value = app->memory.data_get(app->id, address);
    memory_conf_t conf = app->memory.conf_get(app->id, address);

    /** read gpios if necessary **/
    value = driver_gpio_input(app, conf, address, value);

    return value;
}

data_3bc_t driver_memory_conf_get(app_3bc_t app, address_3bc_t address)
{
    return app->memory.conf_get(app->id, address);
}

/**
 * MACRO: POINTER 
 */
address_3bc_t driver_memory_pointer(app_3bc_t app, address_3bc_t address)
{
    register data_3bc_t ptr = driver_memory_data_get(app, address);

    /**
     * JOKE:
     * 
     * JAVA PROGRAMMER BE LIKE
     * omg i'm scared with null pointer!
     */
    if (ptr == NILL) {
        /** also apply to microsoft java devs (aka C#) */
        driver_program_error(app, ERROR_NULL_POINTER);
    }
    else if (ptr < 0) {
        driver_program_error(app, ERROR_NUMBER_NEGATIVE);
    }

    return (address_3bc_t) ptr;
}

void driver_memory_validate(app_3bc_t app, memory_conf_t conf)
{
    /** optimize **/
    if (conf == 0) {
        return;
    }
    /** not allow pullup and analogic some times **/
    if (BITFIELD_HAS(conf, MEM_CONFIG_GPIO_ANAL | MEM_CONFIG_GPIO_PULL)) {
        driver_program_error(app, ERROR_MEMORY_CONFIG);
    }
    /** not allow pullup and output some times **/
    if (BITFIELD_HAS(conf, MEM_CONFIG_GPIO_SEND | MEM_CONFIG_GPIO_PULL)) {
        driver_program_error(app, ERROR_MEMORY_CONFIG);
    }
    /** not allow input and output some times **/
    if (BITFIELD_HAS(conf, MEM_CONFIG_GPIO_SEND | MEM_CONFIG_GPIO_READ)) {
        driver_program_error(app, ERROR_MEMORY_CONFIG);
    }
    /** analogic required input or output **/
    if (BITFIELD_HAS(conf, MEM_CONFIG_GPIO_ANAL) && !(BITFIELD_HAS(conf, MEM_CONFIG_GPIO_READ) || BITFIELD_HAS(conf, MEM_CONFIG_GPIO_SEND))) {
        driver_program_error(app, ERROR_MEMORY_CONFIG);
    }
}

void driver_memory_free(app_3bc_t app, address_3bc_t address)
{
    /** clear cache level 0 **/
    if (app->memory.cache != NULL && app->memory.cache->address == address) {
        app->memory.cache = NULL;
    }

    /** clear memory node **/
    /** TODO: move to ds_memory_llrbt **/
    app->memory.root = ds_memory_llrbt_clear(address, app->memory.root);
}