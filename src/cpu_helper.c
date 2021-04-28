#include "3bc.h"

static data_3bc_t average_sum;
static data_3bc_t average_count;
static bool maxmin_init;
static data_3bc_t maxmin_value;

void before_helper_average()
{
    average_count = 0;
    average_sum = 0;
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
    maxmin_init = false;
}

void after_helper_maxmin()
{
    /** values is empty **/
    if(!maxmin_init) {
        lang_driver_error(ERROR_VOID_HELPER_MAX_MIN);
    }
    /** update memory aux with better value **/
    tape_aux_set(maxmin_value);
}

/**
 * Calculate average between numbers
 */
void cpu_helper_average(PARAMS_DEFINE)
{   
    VALIDATE_NOT_DUALITY
    /** add number to average **/
    average_sum += GET_ANY_PARAM;
    average_count += 1;

    /** recalculate average **/
    tape_aux_set(average_sum/average_count);
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
    
    if (!maxmin_init || maxmin_value < AUX) {
        maxmin_value = AUX;
        maxmin_init = true;
    }

}

/**
 * Aux memory uses bigger value
 */
void cpu_helper_min(PARAMS_DEFINE)
{
    VALIDATE_NOT_DUALITY
    AUX_USE_ANY_PARAM
    
    if (!maxmin_init || maxmin_value > AUX) {
        maxmin_value = AUX;
        maxmin_init = true;
    }

}