#include "3bc.h"

static cch_t channel_cpu_mode;

/**
 * switch between cpu mode channels
 */
void tape_router_cpu_set(cch_t value)
{
    /** prevent enter in invalid cpu mode **/
    if (value >= tape_program_cpu_size()) {
        lang_driver_error(ERROR_INVALID_CPU);
    }

    /** after cpu mode change **/
    switch (channel_cpu_mode) {
        case MODE_HELPER_SORT:
            after_helper_sort();
            break;

        case MODE_HELPER_MAX:
        case MODE_HELPER_MIN:
            after_helper_maxmin();
            break;

        default:
            break;

    }

    /** before cpu mode change **/
    switch (value) {
        case MODE_HELPER_AVARAGE:
            before_helper_average();
            break;

        case MODE_HELPER_SORT:
            before_helper_sort();
            break;

        case MODE_HELPER_MAX:
        case MODE_HELPER_MIN:
            before_helper_maxmin();
            break;
        
        default:
            break;
    }

    /** apply cpu mode **/
    channel_cpu_mode = value;    
}

/**
 * current cpu channel
 * ALIAS: CMODE
 */
cch_t tape_router_cpu_get()
{
    return channel_cpu_mode;
}