#define TBC_SOURCE_ENTRY
#include "3bc.h"

/**
 * JOKE:
 *
 * crige commentary,
 * cringe-oriented programming,
 * following a lot of documented emoji smileys.
 * U+1F44A U+26BD
 */

#if defined(TBC_ARCH_CPU_AVR)
extern volatile unsigned long timer0_overflow_count;
#endif

static union global_time_u global_time;

bool driver_idle(struct app_3bc_s* const app)
{
    switch (app->cache_l1.sleep_mode) {
    case SLEEP_3BC_REAL_TICK:
#if defined(TBC_P_COMPUTER_OLD)
        return false;
#elif defined(TBC_ARCH_CPU_AVR)
        global_time.count = timer0_overflow_count;
#elif defined(TBC_P_COMPUTER)
        global_time.count = clock();
#endif
        if (app->cache_l3.sleep_called == 0) {
            app->cache_l3.sleep_called = global_time.count;
        } else if (app->cache_l2.sleep_period
            <= (global_time.count - app->cache_l3.sleep_called)) {
            return false;
        }
        return true;

    case SLEEP_3BC_FAKE_TICK:
        /** soo easy and portable =D **/
        return app->cache_l2.sleep_period--;

    case SLEEP_3BC_MICROSECONDS:
#if defined(TBC_P_COMPUTER_OLD)
        return false;
#elif defined(TBC_USE_ARDUINO)
        /**
         * AVR chips provide 8 microsecond accuracy in this vm.
         */
        global_time.micros = micros();

        /** first :D **/
        if (app->cache_l3.sleep_called == 0) {
            app->cache_l3.sleep_called = global_time.micros;
        }
        /** something between 4 or 8 microseconds passed maybe. (o.O) **/
        else if ((global_time.micros - app->cache_l3.sleep_called) >= 1) {
            app->cache_l3.sleep_called = global_time.micros;
            app->cache_l2.sleep_period -= 1;
        }

        return app->cache_l2.sleep_period;

#elif defined(TBC_P_COMPUTER)
        clock_gettime(CLOCK_REALTIME, &global_time.ts);

        /** first :D **/
        if (app->cache_l3.sleep_called == 0) {
            app->cache_l3.sleep_called = global_time.ts.tv_nsec;
        }
        /** one millisecond has passed **/
        else if ((global_time.ts.tv_nsec - app->cache_l3.sleep_called)
            >= 1000) {
            app->cache_l3.sleep_called
                = global_time.ts.tv_nsec; /** reset ref **/
            app->cache_l2.sleep_period -= 1; /** decrease seconds left **/
        }

        return app->cache_l2.sleep_period;

#endif

    case SLEEP_3BC_MILLISECONDS:
#if defined(TBC_P_COMPUTER_OLD)
        return false;
#elif defined(TBC_USE_ARDUINO)
        /**
         * AVR chips provide 12 microsecond accuracy in this vm.
         */
        global_time.micros = micros();

        /** first :D **/
        if (app->cache_l3.sleep_called == 0) {
            app->cache_l3.sleep_called = global_time.micros;
        }
        /** one millisecond has passed **/
        else if ((global_time.micros - app->cache_l3.sleep_called) >= 1000) {
            app->cache_l3.sleep_called = global_time.micros;
            app->cache_l2.sleep_period -= 1;
        }

        return app->cache_l2.sleep_period;

#elif defined(TBC_P_COMPUTER)
        /**
         * TODO: 40 milliseconds is not such a good precision,
         * the algorithm should be improved for this case.
         */
        clock_gettime(CLOCK_REALTIME, &global_time.ts);

        /** first :D **/
        if (app->cache_l3.sleep_called == 0) {
            app->cache_l3.sleep_called = global_time.ts.tv_nsec;
        }
        /** one second has passed **/
        else if ((global_time.ts.tv_nsec - app->cache_l3.sleep_called)
            >= 1000000LU) {
            app->cache_l3.sleep_called
                = global_time.ts.tv_nsec; /** reset ref **/
            app->cache_l2.sleep_period -= 1; /** decrease seconds left **/
        }

        return app->cache_l2.sleep_period;
#endif

    case SLEEP_3BC_SECONDS:
#if defined(TBC_P_COMPUTER_OLD)
        return false;
#elif defined(TBC_USE_ARDUINO)
        /**
         * AVR chips has dedicated timekeeping hardware,
         * which provides 1 millisecond accuracy.
         */
        global_time.millis = millis();

        /** first :D **/
        if (app->cache_l3.sleep_called == 0) {
            app->cache_l3.sleep_called = global_time.millis;
        }
        /** one second passed (safe overflow) **/
        else if ((global_time.millis - app->cache_l3.sleep_called) >= 1000) {
            app->cache_l3.sleep_called = global_time.millis;
            app->cache_l2.sleep_period -= 1;
        }
        return app->cache_l2.sleep_period;

#elif defined(TBC_P_COMPUTER)
        /**
         * this method loses an accuracy of 50 milliseconds,
         * in better performance tradeoff.
         */
        clock_gettime(CLOCK_REALTIME, &global_time.ts);

        /** first :D */
        if (app->cache_l3.sleep_called == 0) {
            app->cache_l3.sleep_called = global_time.ts.tv_nsec;
        }
        /** detect entry to overfllow **/
        else if (!(app->cache_l3.sleep_called & 1)
            && ((global_time.ts.tv_nsec - app->cache_l3.sleep_called) >> 32)) {
            /**
             * NOTE:
             * few less significant bits are unusable cuz their inaccuracy,
             * so nothing better than storing data and saving space. XD
             */
            app->cache_l3.sleep_called |= 1; /** storage over flow**/
        }
        /** detect exit from overflow (exactly 1 second passed) **/
        else if ((app->cache_l3.sleep_called & 1)
            && !((global_time.ts.tv_nsec - app->cache_l3.sleep_called) >> 32)) {
            app->cache_l3.sleep_called ^= 1; /** reset overflow **/
            app->cache_l2.sleep_period -= 1; /** decrease seconds left **/
        }

        return app->cache_l2.sleep_period;

#endif
    }
}
