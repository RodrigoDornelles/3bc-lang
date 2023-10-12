#include "i18n_0000.h"
#include "detect/detect_compiler.h"
#include "pre/pre_date.h"
#include "types/types_null.h"

static const char ___i18n_cli_info_000[] = "[3BC] VIRTUAL MACHINE INFO\n";
static const char ___i18n_cli_info_001[] = "> AUTHOR: Rodrigo Dornelles\n";
static const char ___i18n_cli_info_002[] = "> LICENSE: AGPL 3.0 or higher\n";
static const char ___i18n_cli_info_003[] = "> VERSION: ";
static const char ___i18n_cli_info_006[] = "> COMPILER: ";
static const char ___i18n_cli_info_007[] = TBC_COMPILER_FULLNAME"\n";
static const char ___i18n_cli_info_008[] = "> BUILD DATE: ";
static const char ___i18n_cli_info_009[] = {
   TBC_YEAR_CH0, TBC_YEAR_CH1, TBC_YEAR_CH2, TBC_YEAR_CH3,
    '-', TBC_MONTH_CH0, TBC_MONTH_CH1,
    '-', TBC_DAY_CH0, TBC_DAY_CH1,
    '\n', '\0'
};
static const char ___i18n_cli_info_010[] = "> STACK SIZE: ";
static const char ___i18n_cli_info_013[] = "> STACK FREE: ";
static const char ___i18n_cli_info_016[] = "> OBJECT SIZE: ";
static const char ___i18n_cli_info_018[] = " (bytes)\n";

static const tbc_info_txt_st ___i18n_cli_info_txts[] = {
    {sizeof(___i18n_cli_info_000), (char *const)___i18n_cli_info_000},
    {sizeof(___i18n_cli_info_001), (char *const)___i18n_cli_info_001},
    {sizeof(___i18n_cli_info_002), (char *const)___i18n_cli_info_002},
    {sizeof(___i18n_cli_info_003), (char *const)___i18n_cli_info_003},
    {0, NULL},
    {0, NULL},
    {sizeof(___i18n_cli_info_006), (char *const)___i18n_cli_info_006},
    {sizeof(___i18n_cli_info_007), (char *const)___i18n_cli_info_007},
    {sizeof(___i18n_cli_info_008), (char *const)___i18n_cli_info_008},
    {sizeof(___i18n_cli_info_009), (char *const)___i18n_cli_info_009},
    {sizeof(___i18n_cli_info_010), (char *const)___i18n_cli_info_010},
    {0, NULL},
    {sizeof(___i18n_cli_info_018), (char *const)___i18n_cli_info_018},
    {sizeof(___i18n_cli_info_013), (char *const)___i18n_cli_info_013},
    {0, NULL},
    {sizeof(___i18n_cli_info_018), (char *const)___i18n_cli_info_018},
    {sizeof(___i18n_cli_info_016), (char *const)___i18n_cli_info_016},
    {0, NULL},
    {sizeof(___i18n_cli_info_018), (char *const)___i18n_cli_info_018},
};

const tbc_info_txt_st* tbc_i18n_info_arr = ___i18n_cli_info_txts;
const tbc_u8_t tbc_i18n_info_len = sizeof(___i18n_cli_info_txts)/sizeof(tbc_info_txt_st);
