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
    app_3bc_t app = ds_container_darray_new();

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

#if defined(_3BC_COMPUTER)
/** TODO: I do not know what to do :/ **/
void driver_power_signal(int sig)
{
    switch (sig)
    {
        case SIGINT:
            driver_power_exit(NULL);
        
        case SIGSEGV:
            driver_program_error(NULL, (enum error_3bc_e) sig);
    }
}
#endif

/**
 * UNSAFE SHUTDOWNS
 */
void driver_power_exit(app_3bc_t app)
{
    /** TODO: move driver_tty_exit **/
    if (app->tty_source.type == STREAM_TYPE_COMPUTER_FILE && app->tty_source.io.file != NULL) {
        fclose(app->tty_source.io.file);
    }

    /** deallocate occupied memory **/
    tape_memory_destroy(app);
    tape_program_destroy(app);

    driver_tty_exit();
}
