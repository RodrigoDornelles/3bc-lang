/**
 *  ___________  _____   _
 * |____ | ___ \/  __ \ | |
 *     / / |_/ /| /  \/ | | __ _ _ __   __ _ _   _  __ _  __ _  ___
 *     \ \ ___ \| |     | |/ _` | '_ \ / _` | | | |/ _` |/ _` |/ _ \
 * .___/ / |_/ /| \__/\ | | (_| | | | | (_| | |_| | (_| | (_| |  __/
 * \____/\____/  \____/ |_|\__,_|_| |_|\__, |\__,_|\__,_|\__, |\___|
 *                                     __/ |             __/ |
 *                                    |___/             |___/
 * DESCRIPTION:
 * Code refers to the temporary interruption of the virtual machine,
 * according to a certain time passed.
 *
 * BRIEF:
 * Low-level language, tiny virtual machine, intermediate representation,
 * embeddable, easy for beginners. (Friendly Punched cards)
 *
 * AUTHOR:
 * Copyright (C) 2020 Rodrigo Dornelles.
 *
 * LICENSE:
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License,
 * or any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * JOKE:
 * crige commentary,
 * cringe-oriented programming,
 * following a lot of documented emoji smileys.
 * U+1F44A U+26BD
 *
 * TODO:
 * Support esp32/esp8266 real sleep on arduino framework.
 */

#define TBC_SOURCE_ENTRY
#include "3bc.h"

#if defined(TBC_ARCH_CPU_AVR)
extern volatile unsigned long timer0_overflow_count;
#endif

static union global_time_u global_time;

bool driver_idle(struct app_3bc_s* const app)
{
    switch (app->cache_l1.sleep_mode) {
    case SLEEP_3BC_REAL_TICK:
#if defined(TBC_ARCH_CPU_AVR)
        global_time.count = timer0_overflow_count;
#elif defined(TBC_P_COMPUTER) && !defined(TBC_P_COMPUTER_OLD)
        global_time.count = clock();
#else
#if defined(TBC_PRG_WARNING)
#pragma message("[3BC] UNSUPPORTED: SLEEP_3BC_REAL_TICK")
#else
#warning "[3BC] UNSUPPORTED: SLEEP_3BC_REAL_TICK"
#endif
        driver_program_error(app, ERROR_UNSUPPORTED);
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
#if defined(TBC_USE_ARDUINO)

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

#elif defined(TBC_P_COMPUTER) && defined(CLOCK_REALTIME)                       \
    && !defined(TBC_NOT_CLOCK)
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
#else
#if defined(TBC_PRG_WARNING)
#pragma message("[3BC] UNSUPPORTED: SLEEP_3BC_MICROSECONDS")
#else
#warning "[3BC] UNSUPPORTED: SLEEP_3BC_MICROSECONDS"
#endif
        driver_program_error(app, ERROR_UNSUPPORTED);
#endif

    case SLEEP_3BC_MILLISECONDS:
#if defined(TBC_USE_ARDUINO)
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

#elif defined(TBC_P_COMPUTER) && defined(CLOCK_REALTIME)                       \
    && !defined(TBC_NOT_CLOCK)
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
#else
#if defined(TBC_PRG_WARNING)
#pragma message("[3BC] UNSUPPORTED: SLEEP_3BC_MILLISECONDS")
#else
#warning "[3BC] UNSUPPORTED: SLEEP_3BC_MILLISECONDS"
#endif
        driver_program_error(app, ERROR_UNSUPPORTED);
#endif

    case SLEEP_3BC_SECONDS:
#if defined(TBC_USE_ARDUINO)
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

#elif defined(TBC_P_COMPUTER) && defined(CLOCK_REALTIME)                       \
    && !defined(TBC_NOT_CLOCK)
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
#else
#if defined(TBC_PRG_WARNING)
#pragma message("[3BC] UNSUPPORTED: SLEEP_3BC_SECONDS")
#else
#warning "[3BC] UNSUPPORTED: SLEEP_3BC_SECONDS"
#endif
        driver_program_error(app, ERROR_UNSUPPORTED);
#endif
    }
}
