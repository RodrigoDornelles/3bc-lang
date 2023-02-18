#ifndef H_TYPES_CACHE_TBC
#define H_TYPES_CACHE_TBC

#include "types_fsm.h"

typedef struct ___tbc_cache_l0_s tbc_cache_l0_st;

struct ___tbc_dynamic_buffer_s {
    char* storage;
    unsigned int size;
};

struct ___tbc_fixed_buffer_s {
    char storage[7];
    tbc_u8_t size;
};

struct ___tbc_cache_l0_s {
    /** first column (3 bits) */
    tbc_u8_t rx;
    /** second column (9 bits) */
    tbc_u16_t ry;
    /** third column (12 bits)*/
    tbc_u16_t rz;
};

union cache_l1_u {
    tbc_sleep_et sleep_mode;
    /** step of output */
    tbc_u8_t printing;
    /** direction -1 left | 1 right **/
    tbc_i8_t dir;
    /** use for conditionals (same cycle) */
    bool is;
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
