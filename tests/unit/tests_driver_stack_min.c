#include <assert.h>
#include "bus_cfg_0000.h"
#include "driver_stack.h"

const tbc_layout_cfg_st* tbc_cfg_standard = NULL;
const tbc_u8_t tbc_cfg_size = 0;

int main()
{
    /** Test case 1: Stack configuration with missing stack size */
    {
        unsigned char i = 0;
        struct app_3bc_s app = {0};
        do {
            driver_stack_init(&app);
            ++i;
        }
        while(app.rc != TBC_RET_OK && i < 100);
        app.stack.cfgmin.prog->index = 42;
        assert(app.rc == TBC_RET_OK);
        assert(app.stack.cfgmin.prog_index == 42);
        assert(app.stack.cfg.prog == &app.stack.cfgmin.prog_index);
    }
    return 0;
}