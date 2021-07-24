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

    /** read gpios if necessary **/
    driver_memory_gpio(node);

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

void driver_memory_gpio(struct memory_node_s* node) 
{
    /** default configuration **/
    if (node->conf == 0) {
        return;
    }

    /** not using gpio mode **/
    if ((node->conf & (MEM_CONFIG_GPIO_SEND | MEM_CONFIG_GPIO_READ)) == 0) {
        return;
    }

    /**
     * I hate to do two inline conditional branches (if),
     * it makes me feel like a bad code writer,
     * but this is for optimization purposes,
     * so I shouldn't be so dirty!
     */
    if (MEM_CONFIG_GPIO_SEND == (node->conf & MEM_CONFIG_GPIO_SEND)) {
        /** analogic output pwm **/
        if (MEM_CONFIG_GPIO_ANAL == (node->conf & MEM_CONFIG_GPIO_ANAL)) {
            #ifdef _3BC_ARDUINO
            analogWrite(node->address, node->data);
            #endif
        }
        /** digital output **/
        else {
            /** before conversor **/
            node->data = node->data <= 0? 0: 1;

            #ifdef _3BC_ARDUINO
            digitalWrite(node->address, node->data);
            #endif
        }
    } 
    else {
        /** analogic input **/
        if (MEM_CONFIG_GPIO_ANAL == (node->conf & MEM_CONFIG_GPIO_ANAL)) {
            #ifdef _3BC_ARDUINO
            /** 
             * analogicRead returng values between 0 and 1024
             * abstract precision to go from 0 to 255.
             */
            node->data = analogRead(node->address) / 4;
            #endif
        }
        /** digital input **/
        else {
            #ifdef _3BC_ARDUINO
            node->data = digitalRead(node->address);
            #endif

            /** after conversor **/
            node->data = node->data <= 0? 0: 1;
        }
        /** refresh data inner limits **/
        driver_memory_reload(node);
    }
}

void driver_memory_lineup(struct memory_node_s* node)
{
    /** default configuration **/
    if (node->conf == 0) {
        return;
    }

    /** cache configuration **/
    register bool conf_normalize = (MEM_CONFIG_NORMALIZE == (node->conf & MEM_CONFIG_NORMALIZE));
    register bool conf_max_value = (MEM_CONFIG_MAX_VALUE == (node->conf & MEM_CONFIG_MAX_VALUE));
    register bool conf_min_value = (MEM_CONFIG_MIN_VALUE == (node->conf & MEM_CONFIG_MIN_VALUE));
    register bool conf_gpio_send = (MEM_CONFIG_GPIO_SEND == (node->conf & MEM_CONFIG_GPIO_SEND));
    register bool conf_gpio_read = (MEM_CONFIG_GPIO_READ == (node->conf & MEM_CONFIG_GPIO_READ));
    register bool conf_gpio_anal = (MEM_CONFIG_GPIO_ANAL == (node->conf & MEM_CONFIG_GPIO_ANAL));
    register bool conf_gpio_pull = (MEM_CONFIG_GPIO_PULL == (node->conf & MEM_CONFIG_GPIO_PULL));
    register bool conf_gpio_analogic_write = conf_gpio_anal && conf_gpio_read;
    register bool conf_gpio_analogic_read = conf_gpio_anal && conf_gpio_send;
    register bool conf_gpio_pullup = conf_gpio_pull && conf_gpio_read;
    register bool conf_min_max = conf_max_value && conf_min_value;

    /** not allow pullup and analogic some times **/
    if (conf_gpio_pull && conf_gpio_anal) {
        driver_program_error(ERROR_INVALID_MEMORY_CONFIG);
    }
    /** not allow pullup and output some times **/
    if (conf_gpio_pull && conf_gpio_send) {
        driver_program_error(ERROR_INVALID_MEMORY_CONFIG);
    }
    /** not allow input and output some times **/
    if (conf_gpio_send && conf_gpio_read) {
        driver_program_error(ERROR_INVALID_MEMORY_CONFIG);
    }
    /** analogic required input or output **/
    if (conf_gpio_anal && !(conf_gpio_send || conf_gpio_read)) {
        driver_program_error(ERROR_INVALID_MEMORY_CONFIG);
    }
    /** not allow normalize whitout clamp (limit max & min) **/
    if (conf_normalize && !conf_min_max) {
        driver_program_error(ERROR_INVALID_MEMORY_CONFIG);
    }
    /** verifiy valid value between max & min **/
    if (node->vmin > node->vmax && conf_min_max) {
        driver_program_error(ERROR_INVALID_MEMORY_CLAMP);
    }

    #ifdef _3BC_ARDUINO
    /** digital|analogic output **/
    if(conf_gpio_send) {
        pinMode(node->address, OUTPUT);
    }
    /** digitial input pull up **/
    else if (conf_gpio_pullup) {
        pinMode(node->address, INPUT_PULLUP);
    }
    /** digitial input **/
    else if (conf_gpio_read) {
        pinMode(node->address, INPUT);
    }
    #endif 

    /** flush gpio data **/
    driver_memory_gpio(node);

    /** refresh data inner limits **/
    driver_memory_reload(node);
}


void driver_memory_reload(struct memory_node_s* node)
{
    /** not using limiters mode **/
    if ((node->conf & (MEM_CONFIG_MAX_VALUE | MEM_CONFIG_MIN_VALUE)) == 0) {
        return;
    }

    /** cache normalize configuration **/
    register bool conf_normalize = (MEM_CONFIG_NORMALIZE == (node->conf & MEM_CONFIG_NORMALIZE));

    /** maximum without normalize **/
    if(node->data > node->vmax && !conf_normalize && MEM_CONFIG_MAX_VALUE == (node->conf & MEM_CONFIG_MAX_VALUE)) {
        node->data = node->vmax;
    }
    /** minimum without normalize **/
    else if (node->data < node->vmin && !conf_normalize && MEM_CONFIG_MIN_VALUE == (node->conf & MEM_CONFIG_MIN_VALUE)) {
        node->data = node->vmin;
    }
    /** custom underflow/overflow **/
    else if ((node->vmin > node->data || node->data > node->vmax) && conf_normalize) {
        node->data = ((node->data + node->vmin + 2) % (node->vmax - node->vmin + 1)) + node->vmin;
    }
}

void driver_memory_free(address_3bc_t address)
{
    /** clear cache level 0 **/
    if (APP_3BC->cache_l0 != NULL && APP_3BC->cache_l0->address == address) {
        APP_3BC->cache_l0 = NULL;
    }

    /** clear memory node **/
    APP_3BC->memory.root = tape_memory_llrbt_clear(address, APP_3BC->memory.root);
}