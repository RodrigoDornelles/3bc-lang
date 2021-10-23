#include "3bc.h"

/**
 * switch between cpu mode channels
 */
void tape_router_cpu_set(cpumode_3bc_t value)
{
    if (value >= MODE_END) {
        driver_program_error(ERROR_INVALID_CPU_MODE);
    }

    /** after cpu mode change **/
    switch (APP_3BC->cpu_mode) {
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

        case MODE_HELPER_MAX:
        case MODE_HELPER_MIN:
            before_helper_maxmin();
            break;
        
        default:
            break;
    }

    /** apply cpu mode **/
    APP_3BC->cpu_mode = value;    
}