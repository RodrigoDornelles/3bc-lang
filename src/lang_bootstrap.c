#include "3bc.h"

struct app_3bc_s* lang_bootstrap()
{
    static struct app_3bc_s instance;

    if (!instance.bootstrap) {
        instance.bootstrap = true;
    }

    return &instance;
}