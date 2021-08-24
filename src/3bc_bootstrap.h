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
    }

    return &instance;
}
#endif

#ifdef __cplusplus
}
#endif