#include "3bc.h"

#if defined(_3BC_COMPUTER)
app_3bc_t driver_power_init(int argc, char **argv)
#else
app_3bc_t driver_power_init()
#endif
{
    driver_tty_init();

    #if defined(_3BC_COMPUTER)
    /**
     * Capture computer signals
     */
    signal(SIGINT, driver_power_signal);
    signal(SIGSEGV, driver_power_signal);

    if (argc > 1) {
        APP_3BC->tty_source.type = STREAM_TYPE_COMPUTER_FILE;
        APP_3BC->tty_source.io.file = fopen(argv[argc - 1], "r");
    }

    /** file not found | forbidden **/
    if (APP_3BC->tty_source.type == STREAM_TYPE_COMPUTER_FILE && APP_3BC->tty_source.io.file == NULL) {
        driver_program_error(ERROR_OPEN_FILE);
    }
    #endif

    /** remove macro**/
    return APP_3BC;
}

#if defined(_3BC_COMPUTER)
void driver_power_signal(int sig)
{
    switch (sig)
    {
        case SIGINT:
            driver_power_exit(sig);
        
        case SIGSEGV:
            driver_program_error((enum error_3bc_e) sig);
    }
}
#endif

/**
 * UNSAFE SHUTDOWNS
 */
#if defined(_3BC_COMPUTER)
void driver_power_exit(int sig)
#else
void driver_power_exit()
#endif

{
    #if defined(_3BC_COMPUTER)
    /** close file (safe pointer) **/
    if (APP_3BC->tty_source.type == STREAM_TYPE_COMPUTER_FILE && APP_3BC->tty_source.io.file != NULL) {
        fclose(APP_3BC->tty_source.io.file);
    }
    #endif

    /** deallocate occupied memory **/
    tape_memory_destroy();
    tape_program_destroy();

    driver_tty_exit();
    
    #if defined(_3BC_COMPUTER)
    exit(sig);
    #endif 
}
