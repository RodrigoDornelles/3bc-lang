#include "3bc.h"



#ifdef _3BC_COMPUTER
void lang_driver_init(int argc, char **argv)
#endif
#ifdef _3BC_ARDUINO
void lang_driver_init()
#endif
{
    #ifdef _3BC_COMPUTER
    /**
     * Capture computer signals
     */
    signal(SIGINT, lang_driver_exit);
    signal(SIGSEGV, lang_driver_error);

    APP_3BC->tty_debug.type = STREAM_TYPE_COMPUTER_STD;
    APP_3BC->tty_debug.io.stream = stderr;
    
    APP_3BC->tty_output.type = STREAM_TYPE_COMPUTER_STD;
    APP_3BC->tty_output.io.stream = stdout;

    APP_3BC->tty_keylog.type = STREAM_TYPE_COMPUTER_STD;
    APP_3BC->tty_keylog.io.stream = stdout;
    
    if (argc <= 1) {
        APP_3BC->tty_source.type = STREAM_TYPE_COMPUTER_STD;
        APP_3BC->tty_source.io.stream = stdin;
    }
    else {
        APP_3BC->tty_source.type = STREAM_TYPE_COMPUTER_FILE;
        APP_3BC->tty_source.io.file = fopen(argv[argc - 1], "r");
    }


    /** file not found | forbidden **/
    if (APP_3BC->tty_source.type == STREAM_TYPE_COMPUTER_FILE && APP_3BC->tty_source.io.file == NULL) {
        lang_driver_error(ERROR_OPEN_FILE);
    }
    #endif

    driver_io_init();
}


#ifdef _3BC_COMPUTER
void lang_driver_exit(int sig)
#endif
#ifdef _3BC_ARDUINO
void lang_driver_exit()
#endif
{
    #ifdef _3BC_COMPUTER
    /** close file (safe pointer) **/
    if (APP_3BC->tty_source.type == STREAM_TYPE_COMPUTER_FILE && APP_3BC->tty_source.io.file != NULL) {
        fclose(APP_3BC->tty_source.io.file);
    }
    #endif

    /** deallocate occupied memory **/
    driver_io_exit();
    tape_memory_destroy();
    tape_program_destroy();
    tape_sort_destroy();

    #ifdef _3BC_COMPUTER
    exit(sig);
    #endif
}