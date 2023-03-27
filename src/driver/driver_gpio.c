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
 * Code refers to input and outputs of generic prouposes connecting pins.
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
 * @todo
 * Support raspberry pico
 * Support raspberry pi
 * Support microbit
 * Support ESP IDF
 */

#define TBC_SOURCE_ENTRY
#include "3bc.h"

void driver_gpio_setup(
    struct app_3bc_s* const app, memory_conf_t conf, address_3bc_t pin)
{
    /** nothing use gpio´s pins */
    if (conf == 0
        || (conf & (MEM_CONFIG_GPIO_SEND | MEM_CONFIG_GPIO_READ)) == 0) {
        return;
    }

    /** digital output **/
    if (BITFIELD_HAS(conf, MEM_CONFIG_GPIO_SEND)) {
#if defined(_3BC_ARDUINO)
        pinMode(pin, OUTPUT);
#endif
    }
    /** digital input pull up **/
    else if (BITFIELD_HAS(conf, MEM_CONFIG_GPIO_PULL | MEM_CONFIG_GPIO_READ)) {
#if defined(_3BC_ARDUINO)
        pinMode(pin, INPUT_PULLUP);
#endif
    }
    /** digitial input **/
    else if (BITFIELD_HAS(conf, MEM_CONFIG_GPIO_READ)) {
#if defined(_3BC_ARDUINO)
        pinMode(pin, INPUT);
#endif
    }
}

void driver_gpio_output(struct app_3bc_s* const app, memory_conf_t conf,
    address_3bc_t pin, data_3bc_t data)
{
    if (conf == 0) {
        return;
    }

    if (BITFIELD_HAS(conf, MEM_CONFIG_GPIO_SEND | MEM_CONFIG_GPIO_ANAL)) {
#if defined(_3BC_ARDUINO) && defined(ESP32)
        driver_program_error(app, ERROR_UNSUPPORTED);
#elif defined(_3BC_ARDUINO)
        analogWrite(pin, data);
#endif
    } else if (BITFIELD_HAS(conf, MEM_CONFIG_GPIO_SEND)) {
#if defined(_3BC_ARDUINO)
        digitalWrite(pin, data > 0);
#endif
    }
}

data_3bc_t driver_gpio_input(struct app_3bc_s* const app, memory_conf_t conf,
    address_3bc_t pin, data_3bc_t default_data)
{
    if (conf == 0) {
        return default_data;
    }

    if (BITFIELD_HAS(conf, MEM_CONFIG_GPIO_READ | MEM_CONFIG_GPIO_ANAL)) {
#if defined(_3BC_ARDUINO)
        /**
         * analogicRead returng values between 0 and 1024
         * abstract precision to go from 0 to 255.
         */
        return analogRead(pin) / 4;
#else
        /** when gpio is not implemented **/
        return 0;
#endif
    }
    if (BITFIELD_HAS(conf, MEM_CONFIG_GPIO_READ)) {
#if defined(_3BC_ARDUINO)
        return digitalRead(pin);
#else
        /** when gpio is not implemented **/
        return 0;
#endif
    }

    return default_data;
}

/**
 * JOKE:
 * I hate to do two inline conditional branches (if),
 * it makes me feel like a bad code writer,
 * but this is for optimization purposes,
 * so I shouldn't be so dirty!
 *
 * NOTE:
 * this joke is very good, but this one is outdated,
 * I'll keep it because it's funny!
 *
 * CODE:
 *  if (MEM_CONFIG_GPIO_SEND == (node->conf & MEM_CONFIG_GPIO_SEND)) {
 *      if (MEM_CONFIG_GPIO_ANAL == (node->conf & MEM_CONFIG_GPIO_ANAL)) {}
 *       else {}
 *       ...
 *   ...
 */
