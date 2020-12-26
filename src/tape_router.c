#include "3bc.h"

static cch_t channel_cpu_mode;

void tape_router_cpu_set(cch_t value)
{
    channel_cpu_mode = value;
}

cch_t tape_router_cpu_get()
{
    return channel_cpu_mode;
}