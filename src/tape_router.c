#include "3bc.h"

static cch_t channel_cpu_mode;

/**
 * switch between cpu mode channels
 */
void tape_router_cpu_set(cch_t value)
{
    /** prevent enter in invalid cpu mode **/
    if (value < 0 || value >= (sizeof(instructions)/sizeof(instructions[0])) ) {
        lang_driver_error(ERROR_CPU_INVALID);
    }

    /** after cpu mode change **/
    switch (channel_cpu_mode) {
        default:
            break;

    }

    /** before cpu mode change **/
    switch (value) {
        case MODE_MATH_AVARAGE:
            before_mode_math_average();
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