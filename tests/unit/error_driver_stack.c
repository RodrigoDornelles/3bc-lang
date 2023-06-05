#include <assert.h>
#include "bus_cfg_0000.h"
#include "driver_stack.h"

static const tbc_layout_cfg_st ___layout_cfg[] = {{32}};
const tbc_layout_cfg_st* tbc_cfg_standard = ___layout_cfg;
const tbc_u8_t tbc_cfg_size = 1;

int main()
{
    {
        unsigned char i = 0;
        struct app_3bc_s app = {0};
        unsigned char stack[16] = {0};
        app.stack.raw.buffer = (unsigned char**) &stack;
        while(app.rc != TBC_RET_THROW_ERROR && i < 100) {
            driver_stack(&app);
            ++i;
        }
        assert(app.rc == TBC_RET_THROW_ERROR);
        assert(app.cache_l1.error == ERROR_MEM_STACK_CFG_MIS);
    }
    {
        unsigned char i = 0;
        struct app_3bc_s app = {0};
        unsigned char stack[4] = {sizeof(stack)};
        app.stack.raw.buffer = (unsigned char**) &stack;
        while(app.rc != TBC_RET_THROW_ERROR && i < 100) {
            driver_stack(&app);
            ++i;
        }
        assert(app.rc == TBC_RET_THROW_ERROR);
        assert(app.cache_l1.error == ERROR_MEM_STACK_CFG_MIN);
    }
    {
        unsigned char i = 0;
        struct app_3bc_s app = {0};
        unsigned char stack[16] = {sizeof(stack)};
        app.stack.raw.buffer = (unsigned char**) &stack;
        while(app.rc != TBC_RET_THROW_ERROR && i < 100) {
            driver_stack(&app);
            ++i;
        }
        assert(app.rc == TBC_RET_THROW_ERROR);
        assert(app.cache_l1.error == ERROR_MEM_STACK_CFG_OUT);
    }
}