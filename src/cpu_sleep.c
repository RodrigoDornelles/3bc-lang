#define _3BC_SCU_FIX_2
#include "3bc.h"

void cpu_sleep_real(PARAMS_DEFINE)
{
    REQUIRED_ANY
    VALIDATE_NOT_DUALITY
    VALIDATE_NOT_NEGATIVES
    app->cache_l1.sleep_mode = SLEEP_3BC_REAL_TICK;
    app->cache_l2.sleep_period = GET_ANY_PARAM;
}

void cpu_sleep_fake(PARAMS_DEFINE)
{
    REQUIRED_ANY
    VALIDATE_NOT_DUALITY
    VALIDATE_NOT_NEGATIVES
    app->cache_l1.sleep_mode = SLEEP_3BC_FAKE_TICK;
    app->cache_l2.sleep_period = GET_ANY_PARAM;
}

void cpu_sleep_micr(PARAMS_DEFINE)
{
    REQUIRED_ANY
    VALIDATE_NOT_DUALITY
    VALIDATE_NOT_NEGATIVES
    app->cache_l1.sleep_mode = SLEEP_3BC_MICROSECONDS;
    app->cache_l2.sleep_period = GET_ANY_PARAM;
}

void cpu_sleep_mili(PARAMS_DEFINE)
{
    REQUIRED_ANY
    VALIDATE_NOT_DUALITY
    VALIDATE_NOT_NEGATIVES
    app->cache_l1.sleep_mode = SLEEP_3BC_MILLISECONDS;
    app->cache_l2.sleep_period = GET_ANY_PARAM;
}

void cpu_sleep_seco(PARAMS_DEFINE)
{
    REQUIRED_ANY
    VALIDATE_NOT_DUALITY
    VALIDATE_NOT_NEGATIVES
    app->cache_l1.sleep_mode = SLEEP_3BC_SECONDS;
    app->cache_l2.sleep_period = GET_ANY_PARAM;
}
