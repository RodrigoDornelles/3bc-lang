#include "3bc.h"

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
            switch (interpreter_read(app))
            {
                case 1:
                    app->state = FSM_3BC_RUNNING;
                    return true;

                case 2:
                    app->state = FSM_3BC_STOPED;
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
         * FINAL CONTEXT
         */
        case FSM_3BC_STOPED:
            return false;
    }
}