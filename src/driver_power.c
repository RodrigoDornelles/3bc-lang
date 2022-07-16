#define TBC_SOURCE_ENTRY
#include "3bc.h"

/**
 * MACRO: lang_3bc_init
 */
#if defined(TBC_P_COMPUTER)
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
    struct app_3bc_s* app;

    /**
     * JOKE:
     *
     * Finally, C ANSI FOREACH!!!!
     */
    while ((app = *(apps++)) != NULL) {
        switch (sig) {
        case SIGTERM:
            driver_power_exit(app);
            break;

#if defined(SIGINT)
        case SIGINT:
            driver_power_exit(app);
            break;
#endif

#if defined(SIGSEGV)
        case SIGSEGV:
            driver_program_error(app, (enum error_3bc_e)sig);
            break;
#endif
        }
    }

#if defined(SIGINT)
    exit(sig);
#endif
}

void driver_power_exit(struct app_3bc_s* const app)
{
    if (app->state != FSM_3BC_STOPED) {
        /** TODO: move driver_tty_exit **/
        if (app->tty_source.type == STREAM_TYPE_COMPUTER_FILE
            && app->tty_source.io.file != NULL) {
            fclose(app->tty_source.io.file);
        }
        /** deallocate occupied memory **/
        ds_memory_llrbt_destroy(app);
        ds_program_fifo_destroy(app);

        driver_tty_exit();
        app->state = FSM_3BC_STOPED;
    }
}
