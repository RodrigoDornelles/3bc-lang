#ifndef H_UTIL_DSL_TBC
#define H_UTIL_DSL_TBC

#include "types/types_primitive.h"

typedef union ___tbc_keyword_key_u tbc_keyword_ut;

union ___tbc_keyword_key_u {
    char name[4];
    tbc_i32_t compare;
};

tbc_i8_t util_dsl_split(char** dest, tbc_u8_t* destn, char* src, tbc_u8_t dn, tbc_u8_t sn);
tbc_i8_t util_dsl_line(char **beg, char **mid, char **end, char *src, tbc_u8_t sn);
tbc_i16_t util_dsl_keyword(const char *const src,  const char *const keys, tbc_u16_t kn);

#endif
