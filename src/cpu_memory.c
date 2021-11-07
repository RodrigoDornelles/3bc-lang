#include "3bc.h"

void cpu_memory_free(PARAMS_DEFINE)
{
    REQUIRED_ADDRESS
    VALIDATE_NOT_VALUES
    driver_memory_free(address);
}

void cpu_memory_aloc(PARAMS_DEFINE)
{
    REQUIRED_ADDRESS
    driver_memory_data_set(address, value);
}

void cpu_memory_moff(PARAMS_DEFINE)
{
    REQUIRED_ADDRESS
    /** config remove mask (and not) */
    driver_memory_conf_set(address, driver_memory_conf_get(address) &~ value);
}

void cpu_memory_muse(PARAMS_DEFINE)
{
    REQUIRED_ADDRESS
    /** config append mask (or) */
    driver_memory_conf_set(address, driver_memory_conf_get(address) | value);
}

void cpu_memory_ptr_free(PARAMS_DEFINE)
{
    REQUIRED_ADDRESS
    VALIDATE_NOT_VALUES
    driver_memory_free(POINTER(address));
}

void cpu_memory_ptr_aloc(PARAMS_DEFINE)
{
    REQUIRED_ADDRESS
    driver_memory_data_set(POINTER(address), value);
}

void cpu_memory_ptr_pull(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    driver_memory_data_set(POINTER(address), AUX);
}

void cpu_memory_ptr_push(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    driver_accumulator_set(driver_memory_data_get(POINTER(address)));
}

void cpu_memory_ptr_spin(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    {
        data_3bc_t aux_old = AUX;
        address = POINTER(address);
        driver_accumulator_set(driver_memory_data_get(address));
        driver_memory_data_set(address, aux_old);
    }
}

void cpu_memory_aux_free(PARAMS_DEFINE)
{
    VALIDATE_NOT_ADRESS
    VALIDATE_NOT_VALUES
    driver_accumulator_set(NILL);
}

void cpu_memory_aux_aloc(PARAMS_DEFINE)
{
    VALIDATE_NOT_ADRESS
    driver_accumulator_set(value);
}

void cpu_memory_aux_pull(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    driver_memory_data_set(address, AUX);
}

void cpu_memory_aux_push(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    driver_accumulator_set(driver_memory_data_get(address));
}

/**
 * invert values inner AUX & Memory
 */
void cpu_memory_aux_spin(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    {
        data_3bc_t aux_old = AUX;
        driver_accumulator_set(driver_memory_data_get(address));
        driver_memory_data_set(address, aux_old);
    }
}