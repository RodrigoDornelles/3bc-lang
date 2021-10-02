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
#define lang_run                 driver_program_run
#define lang_init                driver_power_init
#define lang_exit                driver_power_exit
#define lang_line                tape_program_line_add
#define lang_io_call(tty,l);     APP_3BC->tty.type=STREAM_TYPE_FUNCTION_CALL;APP_3BC->tty.io.lambda=l;
#define lang_fpga                ds_fpg_array_func_set
/**
 * SINGLETON
 * MACRO: APP_3BC
 */
#ifdef __cplusplus
extern "C" {
#endif

struct app_3bc_s* bootstrap_3bc();

#ifdef _3BC_SCU_FIX
struct app_3bc_s* bootstrap_3bc()
{
    static struct app_3bc_s instance;

    if (!instance.bootstrap) {
        instance.bootstrap = true;
        instance.memory.data_get = &ds_memory_llrbt_data_get;
        instance.memory.vmin_get = &ds_memory_llrbt_vmin_get;
        instance.memory.vmax_get = &ds_memory_llrbt_vmax_get;
        instance.memory.conf_get = &ds_memory_llrbt_conf_get;
        instance.memory.data_set = &ds_memory_llrbt_data_set;
        instance.memory.vmin_set = &ds_memory_llrbt_vmin_set;
        instance.memory.vmax_set = &ds_memory_llrbt_vmax_set;
        instance.memory.conf_set = &ds_memory_llrbt_conf_set;
        #if defined(_3BC_COMPUTER)
        instance.tty_source.type = STREAM_TYPE_COMPUTER_STD;
        instance.tty_source.io.file = stdin;
        instance.tty_debug.type = STREAM_TYPE_COMPUTER_STD;
        instance.tty_debug.io.stream = stderr;
        instance.tty_output.type = STREAM_TYPE_COMPUTER_STD;
        instance.tty_output.io.stream = stdout;
        instance.tty_keylog.type = STREAM_TYPE_CLONE_TTY;
        instance.tty_keylog.io.tty = &instance.tty_output;
        #endif
    }

    return &instance;
}
#endif

#ifdef __cplusplus
}
#endif