#include "3bc.h"

#ifdef _3BC_PC_NOT_WINDOWS
struct termios term_old_attr;
struct termios term_new_attr;
#endif

optional_inline driver_io_init()
{
    #ifdef _3BC_PC_NOT_WINDOWS
    /**
     * Turn possible terminal uncannonical mode 
     * without conio.h in linux/unix builds
     */
    tcgetattr(0, &term_old_attr);
    tcgetattr(0, &term_new_attr);

    term_new_attr.c_lflag &= ~ICANON;
    term_new_attr.c_lflag &= ~ECHO;

    term_new_attr.c_cc[VTIME] = 0;
    term_new_attr.c_cc[VMIN] = 1;
    #endif

    #ifdef _3BC_ARDUINO
    arduino_serial_begin();
    #endif
}

optional_inline driver_io_exit()
{
    #ifdef _3BC_COMPUTER
    /** clear buffers **/
    fflush(stderr);
    fflush(stdout);
    #endif
    
    #ifdef _3BC_PC_NOT_WINDOWS
    /** reset terminal to default mode (linux/unix) **/
    tcsetattr(STDIN_FILENO, TCSANOW, &term_old_attr);
    #endif
}

/**
 * detect keyboard input
 */
data_3bc_t driver_io_input(register_3bc_t type, address_3bc_t addres)
{
    signed int value;
    char c[2] = "\0";
    bool invalid;
    
    do {
        invalid = false;

        /** capture input **/
        #ifdef _3BC_PC_NOT_WINDOWS
        tcsetattr(STDIN_FILENO,TCSANOW, &term_new_attr);
        c[0] = getchar();
        tcsetattr(STDIN_FILENO,TCSANOW, &term_old_attr);
        #endif 

        #ifdef _3BC_PC_WINDOWS
        /** exclusive function of the conio.h library **/
        c[0] = getch();
        #endif

        /** validate input **/
        switch (type) {
            case STRC: 
                /** verify is a ASCII alphabet's letter/symbol **/
                invalid |= (c[0] < 0x20 || c[0] > 0x7E);
                value = c[0];
                break;

            case STRI: 
                invalid |= !sscanf(c, "%d", &value);
                break;
            
            case STRO: 
                invalid |= !sscanf(c, "%o", &value);
                break;

            case STRX:
                invalid |= !sscanf(c, "%x", &value);
                break;
        }

        /** validade input inner memory clamp limits **/
        if ((driver_memory_data_get(addres) & MEM_CONFIG_MIN_VALUE) == MEM_CONFIG_MIN_VALUE) {
            invalid |= driver_memory_vmin_get(addres) > value;
        }
        if ((driver_memory_data_get(addres) & MEM_CONFIG_MAX_VALUE) == MEM_CONFIG_MAX_VALUE) {
            invalid |= driver_memory_vmax_get(addres) < value;
        }
    
    }
    while (invalid);

    return (data_3bc_t) value;
}

/**
 * stream texts to outputs
 */
void driver_io_output(struct tty_3bc_s tty, register_3bc_t type, data_3bc_t val)
{
    char output[16];

    switch (type) {
        case STRC:
            snprintf(output, 16, "%c", abs(val));
            break;
        
        case STRX:
            snprintf(output, 16, "%x", abs(val));
            break;

        case STRI:
            snprintf(output, 16, "%d", abs(val));
            break;

        case STRO:
            snprintf(output, 16, "%o", abs(val));
            break;
    }

    #ifdef _3BC_COMPUTER
    /** negative symbol **/
    if (val < 0) {
        driver_io_output(tty, STRC, '-');
    }

    /** stream standard c output **/
    if (tty.type == STREAM_TYPE_COMPUTER_STD && tty.io.stream == stdout){
        fprintf(stdout, "%s", output);
    }
    /** stream standard c error **/
    else if (tty.type == STREAM_TYPE_COMPUTER_STD && tty.io.stream == stderr){
        fprintf(stderr, "%s", output);
    }
    #endif

    #ifdef _3BC_ARDUINO
    arduino_serial_print(1, output);
    #endif
}

#ifdef _3BC_COMPUTER
void driver_io_signal(int sig)
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