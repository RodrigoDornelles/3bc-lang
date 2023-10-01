#ifndef H_UTIL_STOI_TBC
#define H_UTIL_STOI_TBC

#include "types/types_errors.h"
#include "types/types_primitive.h"

typedef tbc_error_et (*util_stoi_ft)(void *const dest, char *const src, const tbc_u8_t dn, tbc_u8_t sn);

tbc_error_et util_stoi16(void *const dest, char *const src, const tbc_u8_t dn, tbc_u8_t sn);
tbc_error_et util_stoi10(void *const dest, char *const src, const tbc_u8_t dn, tbc_u8_t sn);
tbc_error_et util_stoi8(void *const dest, char *const src, const tbc_u8_t dn, tbc_u8_t sn);
tbc_error_et util_stoi2(void *const dest, char *const src, const tbc_u8_t dn, tbc_u8_t sn);
util_stoi_ft util_stoi_auto(char** dest, tbc_i8_t* dn, char *src, tbc_i8_t sn);

#endif
