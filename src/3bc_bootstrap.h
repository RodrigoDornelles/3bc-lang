#include "3bc.h"

/**
 * LEGACY COMPATIBILITY USER MACROS
 */
#define lang_driver_init         lang_init
#define lang_driver_exit         lang_exit
#define lang_driver_run          lang_run

/**
 * USER MACROS
 */
#define lang_3bc_update          driver_interrupt
#define lang_3bc_init            driver_power_init
#define lang_exit                driver_power_exit
#define lang_line                tape_program_line_add
#define lang_io_call(tty,l);     APP_3BC->tty.type=STREAM_TYPE_FUNCTION_CALL;APP_3BC->tty.io.lambda=l;
#define lang_fpga                custom_3bc_func_set
