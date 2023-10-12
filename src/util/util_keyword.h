#ifndef H_UTIL_KEYWORD_TBC
#define H_UTIL_KEYWORD_TBC

#include "types/types_primitive.h"

typedef struct ___tbc_keyword_s tbc_keyword_st;

union ___tbc_keyword_key_u {
    char name[5];
    tbc_i32_t compare;
};

struct ___tbc_keyword_s {
    union ___tbc_keyword_key_u key;
    tbc_i16_t value;
};

tbc_i16_t util_keyword(const char *const src, const tbc_keyword_st *const kl, tbc_i16_t kn);

#endif
