#define TBC_SOURCE_ENTRY
#include "3bc.h"

#if defined(TBC_ARCH_CPU_AVR)
/** TODO: make compatible with xtensa **/
extern volatile unsigned long timer0_overflow_count;
#endif

bool driver_idle(struct app_3bc_s* const app)
{
    switch(app->cache_l1.sleep_mode)
    {
        case SLEEP_3BC_REAL_TICK: {
#if defined(TBC_P_COMPUTER_OLD)
            return false;
#elif defined(TBC_ARCH_CPU_AVR)
            unsigned long time_now = timer0_overflow_count;
#elif defined(TBC_P_COMPUTER)
            unsigned long time_now = clock();
#endif
            if (app->cache_l3.sleep_called == 0) {
                app->cache_l3.sleep_called = time_now;
            } else if ((time_now - app->cache_l3.sleep_called)
                >= app->cache_l2.sleep_period) {
                return false;
            }
            return true;
        }

        case SLEEP_3BC_FAKE_TICK:
            return app->cache_l2.sleep_period--;

        case SLEEP_3BC_MICROSECONDS:
            #if defined(TBC_P_COMPUTER_OLD)
            return false;
            #elif defined(TBC_USE_ARDUINO)
            {
                unsigned long time_now = micros();
                if (app->cache_l3.sleep_called == 0) {
                    app->cache_l3.sleep_called = time_now;
                } 
                else {
                    time_now -= app->cache_l3.sleep_called;
                    return time_now > app->cache_l2.sleep_period;
                }
            }
            #elif defined (TBC_P_COMPUTER)
            {
                struct timespec time_now;
                clock_gettime(CLOCK_REALTIME, &time_now);

                if (app->cache_l3.sleep_called == 0) {
                    app->cache_l3.sleep_called = time_now.tv_nsec;
                } 
                /** one millisecond has passed **/
                else if ((time_now.tv_nsec - app->cache_l3.sleep_called) >= 1000){
                    app->cache_l3.sleep_called = time_now.tv_nsec; /** reset ref **/
                    app->cache_l2.sleep_period -= 1; /** decrease seconds left **/
                }

                return app->cache_l2.sleep_period;
            }
            #endif

       case SLEEP_3BC_MILLISECONDS:
            #if defined(TBC_P_COMPUTER_OLD)
            return false;
            #elif defined(TBC_USE_ARDUINO)
            {
                unsigned long time_now = millis();
                if (app->cache_l3.sleep_called == 0) {
                    app->cache_l3.sleep_called = time_now;
                } 
                else {
                    time_now -= app->cache_l3.sleep_called;
                    return time_now > app->cache_l2.sleep_period;
                }
            }
            #elif defined(TBC_P_COMPUTER)
            {
                struct timespec time_now;
                clock_gettime(CLOCK_REALTIME, &time_now);

                if (app->cache_l3.sleep_called == 0) {
                    app->cache_l3.sleep_called = time_now.tv_nsec;
                } 
                /** one millisecond has passed **/
                else if ((time_now.tv_nsec - app->cache_l3.sleep_called) >= 1000000LU){
                    app->cache_l3.sleep_called = time_now.tv_nsec; /** reset ref **/
                    app->cache_l2.sleep_period -= 1; /** decrease seconds left **/
                }

                return app->cache_l2.sleep_period;
            }
            #endif

        case SLEEP_3BC_SECONDS:
            #if defined(TBC_P_COMPUTER_OLD)
            return false;
            #elif defined(TBC_USE_ARDUINO)
            {
                unsigned long time_now = millis()/1000;
                if (app->cache_l3.sleep_called == 0) {
                    app->cache_l3.sleep_called = time_now;
                } 
                else {
                    time_now -= app->cache_l3.sleep_called;
                    return time_now > app->cache_l2.sleep_period;
                }
            }
            #elif defined(TBC_P_COMPUTER)
            {
                struct timespec time_now;
                clock_gettime(CLOCK_REALTIME, &time_now);

                /** fist ticket **/
                if (app->cache_l3.sleep_called == 0) {
                    app->cache_l3.sleep_called = time_now.tv_nsec;
                }
                /** detect entry to overfllow **/
                else if (!(app->cache_l3.sleep_called & 1) 
                    && ((time_now.tv_nsec - app->cache_l3.sleep_called) >> 32)) {
                    app->cache_l3.sleep_called |= 1; /** storage over flow**/
                }
                /** detect exit from overflow (exactly 1 second passed) **/
                else if ((app->cache_l3.sleep_called & 1) 
                    && !((time_now.tv_nsec - app->cache_l3.sleep_called) >> 32)) {
                    app->cache_l3.sleep_called ^= 1; /** reset overflow **/
                    app->cache_l2.sleep_period -= 1; /** decrease seconds left **/
                }

                return app->cache_l2.sleep_period;
            }
            #endif
    }
}
