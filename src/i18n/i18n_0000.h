#ifndef H_I18N_0000_TBC
#define H_I18N_0000_TBC

#include "types/types_primitive.h"

enum ___tbc_i18n_common_e {
    I18N_COMMON_VERSION = 0,
    I18N_COMMON_VERPLUS = 1,
    I18N_COMMON_WEBSITE = 2,
};

typedef struct ___tbc_info_txt_s tbc_info_txt_st;

struct ___tbc_info_txt_s {
    tbc_i8_t len;
    const char* ptr;
};

extern const tbc_info_txt_st tbc_i18n_commons[3];
extern const tbc_info_txt_st* tbc_i18n_error_arr;
extern const tbc_info_txt_st* tbc_i18n_help_arr;
extern const tbc_info_txt_st* tbc_i18n_info_arr;
extern const tbc_u8_t tbc_i18n_error_len;
extern const tbc_u8_t tbc_i18n_help_len;
extern const tbc_u8_t tbc_i18n_info_len;

#endif
