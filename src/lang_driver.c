#include "3bc.h"

#define print_file(file,type, val);\
switch(type){\
case STRI: fprintf(file, "%lu", (unsigned long) val); break;\
case STRO: fprintf(file, "%o", (unsigned int) val); break;\
case STRC: fprintf(file, "%c", (unsigned char) val); break;\
case STRX: fprintf(file, "%x", (unsigned int) val); break;\
case STRU: fprintf(file, "%d", (signed int) val); break;} 

struct termios term_old_attr;
struct termios term_new_attr;

void lang_driver_run()
{
    while(tape_program_avaliable()? tape_program_exe(): RETURN_EXIT);
}

void lang_driver_init()
{
    signal(SIGINT, lang_driver_exit);

    tcgetattr(0, &term_old_attr);
    tcgetattr(0, &term_new_attr);

    term_new_attr.c_lflag &= ~ICANON;
    term_new_attr.c_lflag &= ~ECHO;

    term_new_attr.c_cc[VTIME] = 0;
    term_new_attr.c_cc[VMIN] = 1;
}

void lang_driver_exit(int sig)
{
    tcsetattr(STDIN_FILENO,TCSANOW,&term_old_attr);

    tape_memory_destroy();
    tape_program_destroy();
    
    exit(sig);
}

void lang_driver_output_1(reg_t type, val_t val)
{
    print_file(stdout, type, val);
}

void lang_driver_output_2(reg_t type, val_t val)
{
    print_file(stderr, type, val);
}

void lang_driver_error(const char* text)
{
    fprintf(stderr, "%s", text);
}

#ifndef _WIN32
int getch()
{
    int c ;

    tcsetattr(STDIN_FILENO,TCSANOW, &term_new_attr);
    c = getchar() ;
    tcsetattr(STDIN_FILENO,TCSANOW, &term_old_attr);
    return c ;
}
#endif


int getch_parser(const char* format)
{
    static int input_val;
    static char input_key[2] = "\0";

    input_key[0] = getch();
    
    sscanf(input_key, format, &input_val);
    
    return input_val;
}
 