#include "3bc.h"

static val_t average_sum;
static val_t average_count;

RETURN_DEFINE cpu_helper_average(PARAMS_DEFINE)
{   
    VALIDATE_NOT_DUALITY
    /** add number to average **/
    average_sum += GET_ANY_PARAM;
    average_count += 1;

    /** recalculate average **/
    tape_aux_set(average_sum/average_count);
    return RETURN_OK;
}

void before_helper_average()
{
    average_count = 0;
    average_sum = 0;
}