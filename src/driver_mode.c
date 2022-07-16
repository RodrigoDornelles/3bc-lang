#define TBC_SOURCE_ENTRY
#include "3bc.h"

/**
 * switch between cpu mode channels
 */
void driver_mode_set(struct app_3bc_s* const app, cpumode_3bc_t value)
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