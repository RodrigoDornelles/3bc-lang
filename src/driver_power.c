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
 * Code refers startup, shutdown and system signals
 * received by virtual machines.
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
 */

#define TBC_SOURCE_ENTRY
#include "3bc.h"

/**
 * MACRO: lang_3bc_init
 */
#if !defined(TBC_NOT_ARGCV)
struct app_3bc_s* const driver_power_init(int argc, char** argv)
#else
struct app_3bc_s* const driver_power_init()
#endif
{
    struct app_3bc_s* const app = ds_hypervisor_darray_new();

#if defined(TBC_P_COMPUTER)
    /** TODO: move to driver_tty_init() **/
    app->tty_source.type = STREAM_TYPE_COMPUTER_STD;
    app->tty_source.io.file = stdin;
    app->tty_debug.type = STREAM_TYPE_COMPUTER_STD;
    app->tty_debug.io.stream = stderr;
    app->tty_output.type = STREAM_TYPE_COMPUTER_STD;
    app->tty_output.io.stream = stdout;
    app->tty_keylog.type = STREAM_TYPE_CLONE_TTY;
    app->tty_keylog.io.tty = &app->tty_output;
    app->tty_error.type = STREAM_TYPE_COMPUTER_STD;
    app->tty_error.io.stream = stderr;
#endif

    driver_tty_init();

#if defined(TBC_P_COMPUTER)
/**
 * Capture computer signals
 */
#if defined(SIGINT)
    signal(SIGINT, driver_power_signal);
#endif

#if defined(SIGSEGV)
    signal(SIGSEGV, driver_power_signal);
#endif
#if !defined(TBC_NOT_ARGCV) && !defined(TBC_NOT_FILES)
    if (argc > 1) {
        app->tty_source.type = STREAM_TYPE_COMPUTER_FILE;
        app->tty_source.io.file = fopen(argv[argc - 1], "r");
    }

    /** file not found | forbidden **/
    if (app->tty_source.type == STREAM_TYPE_COMPUTER_FILE
        && app->tty_source.io.file == NULL) {
        driver_program_error(app, ERROR_OPEN_FILE);
    }
#endif
#endif

    return app;
}

/**
 * JOKE:
 *
 * The Hypervisor is crazy!!
 * anything dangerous, everything is down!!
 */
void driver_power_signal(int sig)
{
    struct app_3bc_s** apps = ds_hypervisor_darray_get_all();

    /**
     * JOKE:
     *
     * Finally, C ANSI FOREACH!!!!
     */
    while (*apps) {
        switch (sig) {
        case SIGTERM:
            driver_power_exit(*apps);
            break;

#if defined(SIGINT)
        case SIGINT:
            driver_power_exit(*apps);
            break;
#endif

#if defined(SIGSEGV)
        case SIGSEGV:
            driver_program_error(*apps, (enum error_3bc_e)sig);
            break;
#endif
        }
        apps++;
    }

    ds_hypervisor_darray_kill_all();
#if defined(SIGINT)
    exit(sig);
#endif
}

void driver_power_exit(struct app_3bc_s* const app)
{
    if (app->state != FSM_3BC_STOPED) {
        /** TODO: move driver_tty_exit **/
#if !defined(TBC_NOT_FILES)
        if (app->tty_source.type == STREAM_TYPE_COMPUTER_FILE
            && app->tty_source.io.file != NULL) {
            fclose(app->tty_source.io.file);
        }
#endif
        /** deallocate occupied memory **/
        ds_memory_llrbt_destroy(app);
        ds_program_fifo_destroy(app);

        driver_tty_exit();
        app->state = FSM_3BC_STOPED;
    }
}
