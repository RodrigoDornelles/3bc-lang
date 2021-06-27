#include "3bc.h"

struct app_3bc_s* driver_bootstrap()
{
    static struct app_3bc_s instance;

    if (!instance.bootstrap) {
        instance.bootstrap = true;
    }

    return &instance;
}