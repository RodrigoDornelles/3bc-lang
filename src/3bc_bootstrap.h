#include "3bc.h"

struct app_3bc_s* bootstrap_3bc();

#ifdef _3BC_SCU_FIX
/**
 * MACRO: APP_3BC
 */
struct app_3bc_s* bootstrap_3bc()
{
    static struct app_3bc_s instance;

    if (!instance.bootstrap) {
        instance.bootstrap = true;
    }

    return &instance;
}
#endif