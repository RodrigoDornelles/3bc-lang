#define _3BC_SCU_FIX_2
#include "3bc.h"

#if defined(_3BC_ARDUINO) && defined(_3BC_AVR)
/** TODO: make compatible with xtensa **/
extern volatile unsigned long timer0_overflow_count;
#endif

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
            if (!ds_program_fifo_avaliable(app)) {
                app->state = FSM_3BC_READING;
            }
            else if (app->cpu_mode == MODE_SLEEP && app->cache_l1.sleep_mode != SLEEP_3BC_NONE) {
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
            switch (app->cache_l1.sleep_mode)
            {
                case SLEEP_3BC_REAL_TICK:
                {
                    #if defined(_3BC_PC_1970)
                    unsigned long time_now = 0;
                    #elif defined(_3BC_COMPUTER)
                    unsigned long time_now = clock();
                    #elif defined(_3BC_ARDUINO) && defined(_3BC_AVR)
                    unsigned long time_now = timer0_overflow_count;
                    #else
                    unsigned long time_now = 0;
                    #endif
                    if (app->cache_l3.sleep_called == 0) {
                        app->cache_l3.sleep_called = time_now;
                    }
                    else if ((time_now - app->cache_l3.sleep_called) > app->cache_l2.sleep_period) {
                        break;
                    }
                    return true;
                }

                case SLEEP_3BC_FAKE_TICK:    
                {
                    app->cache_l2.sleep_period -= 1;
                    if (app->cache_l2.sleep_period == 0) {
                        break;
                    }
                    return true;
                }

                case SLEEP_3BC_MICROSECONDS:
                {
                    #if defined(_3BC_PC_1970)
                    unsigned long time_now = 0;
                    #elif defined(_3BC_COMPUTER) && defined(CLOCKS_PER_SEC)
                    unsigned long time_now = clock()/(CLOCKS_PER_SEC/1000/1000);
                    #elif defined(_3BC_ARDUINO) && defined(_3BC_AVR)
                    unsigned long time_now = micros();
                    #else
                    unsigned long time_now = 0;
                    #endif
                    if (app->cache_l3.sleep_called == 0) {
                        app->cache_l3.sleep_called = time_now;
                    }
                    else if ((time_now - app->cache_l3.sleep_called) > app->cache_l2.sleep_period) {
                        break;
                    }
                    return true;    
                }

                case SLEEP_3BC_MILLISECONDS:
                {
                    #if defined(_3BC_PC_1970)
                    unsigned long time_now = 0;
                    #elif defined(_3BC_COMPUTER) && defined(CLOCKS_PER_SEC)
                    unsigned long time_now = clock()/(CLOCKS_PER_SEC/1000);
                    #elif defined(_3BC_ARDUINO)
                    unsigned long time_now = millis();
                    #else
                    unsigned long time_now = 0;
                    #endif
                    if (app->cache_l3.sleep_called == 0) {
                        app->cache_l3.sleep_called = time_now;
                    }
                    else if ((time_now - app->cache_l3.sleep_called) > app->cache_l2.sleep_period) {
                        break;
                    }
                    return true;
                }

                case SLEEP_3BC_SECONDS:
                {
                    #if defined(_3BC_PC_1970)
                    unsigned long time_now = 0;
                    #elif defined(_3BC_COMPUTER)
                    unsigned long time_now = time(NULL);
                    #elif defined(_3BC_ARDUINO)
                    unsigned long time_now = millis()/1000;
                    #else
                    unsigned long time_now = 0;
                    #endif
                    if (app->cache_l3.sleep_called == 0) {
                        app->cache_l3.sleep_called = time_now;
                    }
                    else if ((time_now - app->cache_l3.sleep_called) > app->cache_l2.sleep_period) {
                        break;
                    }
                    return true;
                }
            }
            app->state = FSM_3BC_RUNNING;
            app->cache_l1.sleep_mode = SLEEP_3BC_NONE;
            app->cache_l2.sleep_period = 0;
            app->cache_l3.sleep_called = 0;
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