#ifndef H_UTIL_DSL_TBC
#define H_UTIL_DSL_TBC

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

tbc_i8_t util_dsl_split(char** dest, tbc_u8_t* destn, char* src, tbc_u8_t dn, tbc_u8_t sn);
tbc_i8_t util_dsl_line(char **beg, char **mid, char **end, char *src, tbc_u8_t sn);
tbc_i16_t util_dsl_keyword(const char *const src, const tbc_keyword_st *const kl, tbc_i16_t kn);

#endif
