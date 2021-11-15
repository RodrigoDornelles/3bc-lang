#define _3BC_SCU_FIX_2
#include "3bc.h"

/**
 * VM processor context manager, allows asychronism.
 */
bool driver_interrupt(app_3bc_t app)
{
    switch (app->state)
    {
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
            #if defined(_3BC_DISABLE_INTERPRETER)
            switch (EOF)
            #else
            switch (interpreter_3bc(app))
            #endif
            {
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
            if (!tape_program_avaliable(app)) {
                app->state = FSM_3BC_READING;
            }
            /** TODO: this
            else if (false) {
                app->state = FSM_3BC_WAITING;
            }
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
            if (false /** todo **/) {
                app->state = FSM_3BC_RUNNING;
            }
            return true;

        /**
         * INPUT CONTEXT
         */
        case FSM_3BC_IO_READ:
            app->state = FSM_3BC_RUNNING;
            return true;

        /**
         * OUTPUT CONTEXT
         */
        case FSM_3BC_IO_SEND:
            app->state = FSM_3BC_RUNNING;
            return true;

        /**
         * EXIT CONTEXT
         */
        case FSM_3BC_EXITING:
            #if defined(SIGINT)
            driver_power_exit(0);
            #else 
            driver_power_exit();
            #endif
            app->state = FSM_3BC_STOPED;
            return true;
    }

    return false;
}