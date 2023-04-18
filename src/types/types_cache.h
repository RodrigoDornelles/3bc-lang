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
    tbc_u8_t u8;
    tbc_i8_t i8;
    tbc_error_et error;
    tbc_sleep_et sleep_mode;
    /** use for conditionals (same cycle) */
    bool is; /**< @todo remove **/
};

union cache_l2_u {
    tbc_u8_t u8[4];
    tbc_u16_t u16[2];
    tbc_u32_t u32;
    tbc_i8_t i8[4];
    tbc_i16_t i16[2];
    tbc_i32_t i32;
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
