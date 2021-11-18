#define _3BC_SCU_FIX_2
#include "3bc.h"

/**
 * switch between cpu mode channels
 */
void driver_mode_set(app_3bc_t app, cpumode_3bc_t value)
{
    if (value >= MODE_END) {
        driver_program_error(app, ERROR_INVALID_CPU_MODE);
    }

    /** after cpu mode change **/
    switch (app->cpu_mode) {
    }

    /** before cpu mode change **/
    switch (value) {
    }

    /** apply cpu mode **/
    app->cpu_mode = value;    
}