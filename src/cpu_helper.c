#include "3bc.h"

void before_helper_average()
{
    APP_3BC->cache_l1.average_count = 0;
    APP_3BC->cache_l2.average_sum = 0;
}

void before_helper_sort()
{
    tape_sort_init();
}

void after_helper_sort()
{
    tape_sort_destroy();
}

void before_helper_maxmin()
{
    APP_3BC->cache_l1.maxmin_init = false;
}

void after_helper_maxmin()
{
    /** values is empty **/
    if(!APP_3BC->cache_l1.maxmin_init) {
        lang_driver_error(ERROR_VOID_HELPER_MAX_MIN);
    }
    /** update memory aux with better value **/
    tape_aux_set(APP_3BC->cache_l2.maxmin_value);
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
    tape_aux_set(APP_3BC->cache_l2.average_sum/APP_3BC->cache_l1.average_count);
}

/**
 * Insert Sort Algorithm
 */
void cpu_helper_sort(PARAMS_DEFINE)
{   
    VALIDATE_NOT_VALUES
    tape_sort_insert(addres);
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