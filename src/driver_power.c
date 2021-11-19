#define _3BC_SCU_FIX_2
#include "3bc.h"

/**
 * MACRO: lang_3bc_init
 */
#if defined(_3BC_COMPUTER)
app_3bc_t driver_power_init(int argc, char **argv)
#else
app_3bc_t driver_power_init()
#endif
{
    app_3bc_t app = ds_hypervisor_darray_new();

    #if defined(_3BC_COMPUTER)
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

    #if defined(_3BC_COMPUTER)
    /**
     * Capture computer signals
     */
    signal(SIGINT, driver_power_signal);
    signal(SIGSEGV, driver_power_signal);

    if (argc > 1) {
        app->tty_source.type = STREAM_TYPE_COMPUTER_FILE;
        app->tty_source.io.file = fopen(argv[argc - 1], "r");
    }

    /** file not found | forbidden **/
    if (app->tty_source.type == STREAM_TYPE_COMPUTER_FILE && app->tty_source.io.file == NULL) {
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
    app_3bc_t* apps = ds_hypervisor_darray_get_all();
    app_3bc_t app;

    /**
     * JOKE:
     *
     * Finally, C ANSI FOREACH!!!!
     */
    while((app = *(++apps)) != NULL) 
    {
        switch (sig)
        {
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
                driver_program_error(app, (enum error_3bc_e) sig);
                break;
            #endif
        }
    }

    #if defined(SIGINT)
    exit(sig);
    #endif
}

void driver_power_exit(app_3bc_t app)
{   
    if (app->state == FSM_3BC_STOPED) {
        return;
    }

    /** TODO: move driver_tty_exit **/
    if (app->tty_source.type == STREAM_TYPE_COMPUTER_FILE && app->tty_source.io.file != NULL) {
        fclose(app->tty_source.io.file);
    }
    /** deallocate occupied memory **/
    tape_memory_destroy(app);
    tape_program_destroy(app);

    driver_tty_exit();
    app->state = FSM_3BC_STOPED;
}
