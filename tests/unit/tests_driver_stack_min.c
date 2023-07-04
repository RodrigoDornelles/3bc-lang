#include <assert.h>
#include "bus/bus_cfg_0000.h"
#include "driver/driver_stack.h"

const tbc_layout_cfg_st* tbc_cfg_standard = NULL;
const tbc_u8_t tbc_cfg_size = 0;

int main()
{
    /** Test case 1: Stack configuration with missing stack size */
    {
        unsigned char i = 0;
        struct app_3bc_s app = {0};
        driver_stack_init(&app, NULL, 0);
        app.stack.cfgmin.prog->index = 42;
        assert(app.rc == TBC_RET_OK);
        assert(app.stack.cfgmin.prog_index == 42);
        assert(app.stack.cfg.prog == &app.stack.cfgmin.prog_index);
    }
    return 0;
}