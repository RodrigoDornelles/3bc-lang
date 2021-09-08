#include "3bc.h"

#if defined(_3BC_PC_NOT_WINDOWS)
struct termios term_old_attr;
struct termios term_new_attr;
#endif

optional_inline driver_io_init()
{
    #if defined(_3BC_PC_NOT_WINDOWS)
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
}

optional_inline driver_io_exit()
{
    #if defined(_3BC_COMPUTER)
    /** clear buffers **/
    fflush(stderr);
    fflush(stdout);
    #endif
    
    #if defined(_3BC_PC_NOT_WINDOWS)
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
        #if defined(_3BC_PC_1970)
        c[0] = cgetc();
        #elif defined(_3BC_PC_NOT_WINDOWS)
        tcsetattr(STDIN_FILENO,TCSANOW, &term_new_attr);
        c[0] = getchar();
        tcsetattr(STDIN_FILENO,TCSANOW, &term_old_attr);
        #elif defined(_3BC_PC_WINDOWS)
        /** exclusive function of the conio.h library **/
        c[0] = getch();
        #endif

        /** validate input **/
        switch (type) {
            case STRB: 
                /** made boolean confirmation **/
                switch(c[0]) {
                    /** pressed YES or TRUE **/
                    case 'Y': case 'y': case '1': value = 1; break;
                    /** pressed YES or FALSE **/
                    case 'N': case 'n': case '0': value = 0; break;
                    /** pressed incorrect option **/
                    default: invalid |= true; break;
                }
                break;

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
    /** the size of the buffer is according to the memory */
    char output[sizeof(data_3bc_t) * 8 + 1];

    /** print negative symbol **/
    if (val < 0 && type != STRC) {
        val = abs(val);
        driver_io_output(tty, STRC, '-');
    }

    switch (type) {
        #ifndef _3BC_MOS6502
        case STRB:
        {
            /**
             * C It doesn't have printing of numbers with binary base,
             * this is very very sad. makes me want to use java!
             */
            int logarithm = val? log2(val): 0;
            int pos = 0;

            do {
                /** concat bitwise to string in reverse order **/
                output[logarithm - pos] = '0' + ((val >> pos) & 1);
            }
            while(pos++ < logarithm);

            /** end of output **/
            output[pos] = '\0';
            break;
        }
        #endif

        case STRC:
            snprintf(output, sizeof(output), "%c", val);
            break;
        
        case STRX:
            snprintf(output, sizeof(output), "%x", val);
            break;

        case STRI:
            snprintf(output, sizeof(output), "%d", val);
            break;

        case STRO:
            snprintf(output, sizeof(output), "%o", val);
            break;

        default:
            driver_program_error(ERROR_UNSUPPORTED);
    }

    #if defined(_3BC_COMPUTER)
    /** stream standard c output **/
    if (tty.type == STREAM_TYPE_COMPUTER_STD){
        fprintf(tty.io.stream, "%s", output);
        return;
    }
    #endif

    if (tty.type == STREAM_TYPE_FUNCTION_CALL) {
        tty.io.lambda(output);
        return;
    }
}

#if defined(_3BC_COMPUTER)
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