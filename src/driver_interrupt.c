#define TBC_SOURCE_ENTRY
#include "3bc.h"

/**
 * VM processor context manager, allows asychronism.
 */
bool driver_interrupt(struct app_3bc_s* const app)
{
    switch (app->state) {
    /**
     * INITIAL CONTEXT
     */
    case FSM_3BC_DEFAULT:
        app->state = FSM_3BC_RUNNING;
        return true;

    /**
     *  INTERPRETER CONTEXT
     */
    case FSM_3BC_READING:
        switch (interpreter_ticket(app)) {
        case 1:
            app->state = FSM_3BC_RUNNING;
            return true;

        case EOF:
            app->state = FSM_3BC_EXITING;
            return true;
        }
        return true;

    /**
     * PROCESS CONTEXT
     */
    case FSM_3BC_RUNNING:
        if (!ds_program_fifo_avaliable(app)) {
            app->state = FSM_3BC_READING;
        } else if (app->cpu_mode == MODE_SLEEP
            && app->cache_l1.sleep_mode != SLEEP_3BC_NONE) {
            app->state = FSM_3BC_WAITING;
        }
        /** TODO
        else if (app->cache_l3.direction < 0) {
            app->state = FSM_3BC_IO_READ;
        }
        else if (app->cache_l3.direction > 0) {
            app->state = FSM_3BC_IO_SEND;
        }*/
        else {
            driver_program_tick(app);
        }
        return true;

    /**
     * SLEEP CONTEXT
     */
    case FSM_3BC_WAITING:
        if (!driver_idle(app)) {
            app->state = FSM_3BC_RUNNING;
            app->cache_l1.sleep_mode = SLEEP_3BC_NONE;
            app->cache_l2.sleep_period = 0;
            app->cache_l3.sleep_called = 0;
        }
        return true;

    /**
     * INPUT CONTEXT
     * TODO: this
    case FSM_3BC_IO_READ:
        app->state = FSM_3BC_RUNNING;
        return true;*/

    /**
     * OUTPUT CONTEXT
     * TODO: this
    case FSM_3BC_IO_SEND:
        app->state = FSM_3BC_RUNNING;
        return true;*/

    /**
     * EXIT CONTEXT
     */
    case FSM_3BC_EXITING:
        driver_power_exit(app);
        return true;
    }

    return false;
}