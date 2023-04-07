#ifndef H_TYPES_CACHE_TBC
#define H_TYPES_CACHE_TBC

#include "types_fsm.h"
#include "types_errors.h"

struct ___tbc_dynamic_buffer_s {
    tbc_i8_t size;
    char* storage;
};

struct ___tbc_fixed_buffer_s {
    tbc_i8_t size;
    char storage[7];
};

union cache_l1_u {
    tbc_error_et error;
    tbc_sleep_et sleep_mode;
    /** use for conditionals (same cycle) */
    bool is; /**< @todo remove **/
};

union cache_l2_u {
    unsigned long sleep_period;
    tbc_tty_st* tty;
};

union cache_l3_u {
    /** fixed buffer */
    struct ___tbc_fixed_buffer_s fixbuf;
    /** dynamic buffer */
    struct ___tbc_dynamic_buffer_s buffer;
    /** auxilary waiting interrupt **/
    unsigned long sleep_called;
};

#endif
