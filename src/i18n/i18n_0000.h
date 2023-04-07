#ifndef H_I18N_0000_TBC
#define H_I18N_0000_TBC

#include "types_primitive.h"

typedef struct ___tbc_error_s tbc_error_st;

struct ___tbc_error_s {
    tbc_u8_t len;
    char* ptr;
};

extern const tbc_error_st* tbc_i18n_error_arr;
extern const tbc_u8_t tbc_i18n_error_len;

#endif
