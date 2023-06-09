#ifndef H_CAST_STOI_TBC
#define H_CAST_STOI_TBC

#include "types_errors.h"
#include "types_primitive.h"

tbc_error_et cast_stoi16(void *const dest, char *const src, const tbc_u8_t dn, tbc_u8_t sn);
tbc_error_et cast_stoi10(void *const dest, char *const src, const tbc_u8_t dn, tbc_u8_t sn);
tbc_error_et cast_stoi8(void *const dest, char *const src, const tbc_u8_t dn, tbc_u8_t sn);
tbc_error_et cast_stoi2(void *const dest, char *const src, const tbc_u8_t dn, tbc_u8_t sn);

#endif
