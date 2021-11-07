#include "3bc.h"

void before_helper_average()
{
    APP_3BC->cache_l1.average_count = 0;
    APP_3BC->cache_l2.average_sum = 0;
}

void before_helper_maxmin()
{
    APP_3BC->cache_l1.maxmin_init = false;
}

void after_helper_maxmin()
{
    /** values is empty **/
    if(!APP_3BC->cache_l1.maxmin_init) {
        driver_program_error(ERROR_VOID_HELPER_MAX_MIN);
    }
    /** update memory aux with better value **/
    driver_accumulator_set(APP_3BC->cache_l2.maxmin_value);
}

/**
 * Calculate average between numbers
 */
void cpu_helper_average(PARAMS_DEFINE)
{   
    VALIDATE_NOT_DUALITY
    /** add number to average **/
    APP_3BC->cache_l1.average_count += 1;
    APP_3BC->cache_l2.average_sum += GET_ANY_PARAM;

    /** recalculate average **/
    driver_accumulator_set(APP_3BC->cache_l2.average_sum/APP_3BC->cache_l1.average_count);
}

/**
 * Aux memory uses bigger value
 */
void cpu_helper_max(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    AUX_USE_ANY_PARAM
    
    if (!APP_3BC->cache_l1.max_init || APP_3BC->cache_l2.max_value < AUX) {
        APP_3BC->cache_l1.max_init = true;
        APP_3BC->cache_l2.max_value = AUX;
    }
}

/**
 * Aux memory uses bigger value
 */
void cpu_helper_min(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    AUX_USE_ANY_PARAM
    
    if (!APP_3BC->cache_l1.min_init || APP_3BC->cache_l2.min_value > AUX) {
        APP_3BC->cache_l1.min_init = true;
        APP_3BC->cache_l2.min_value = AUX;
    }
}

void cpu_helper_percentage(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    #if defined(_3BC_MOS6502)
    driver_program_error(ERROR_UNSUPPORTED);
    #else 
    driver_accumulator_set((data_aux_3bc_t) round((((double) GET_ANY_PARAM)/100.0) * AUX));
    #endif
}

void cpu_helper_reverse(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    {
        data_aux_3bc_t initial = GET_ANY_PARAM;
        data_aux_3bc_t final = 0;
        char base = 0;

        if (reg == NB02) {
            base = 2;
        }
        else if (reg == NB08) {
            base = 8;
        }
        else if (reg == NB10) {
            base = 10;
        }
        else if (reg == NB16) {
            base = 16;
        }

        do {
            final *= base;
            final += (initial % base);
            initial /= base;
        }
        while(initial % base);
        
        driver_accumulator_set(final);
    }
}


void cpu_helper_log2(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    #if defined(_3BC_MOS6502)
    driver_program_error(ERROR_UNSUPPORTED);
    #else 
    driver_accumulator_set((data_aux_3bc_t) round(log2((double) GET_ANY_PARAM)));
    #endif
}

void cpu_helper_log10(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    #if defined(_3BC_MOS6502)
    driver_program_error(ERROR_UNSUPPORTED);
    #else 
    driver_accumulator_set((data_aux_3bc_t) round(log10((double) GET_ANY_PARAM)));
    #endif
}

void cpu_helper_mul_add(PARAMS_DEFINE)
{
    char base = 0;

    if (reg == NB02) {
        base = 2;
    }
    else if (reg == NB08) {
        base = 8;
    }
    else if (reg == NB10) {
        base = 10;
    }
    else if (reg == NB16) {
        base = 16;
    }

    driver_accumulator_set((AUX * base) + GET_ANY_PARAM);
}

void cpu_helper_sign(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    AUX_USE_ANY_PARAM

    if (AUX > 0) {
        driver_accumulator_set(+1);
    }
    else if (AUX < 0) {
        driver_accumulator_set(-1);
    }
    else {
        driver_accumulator_set(0);
    }
}