#include "i18n_0000.h"
#include "detect/detect_compiler.h"
#include "detect/detect_datebuild.h"
#include "types/types_null.h"

static const char ___i18n_cli_info_000[] = "UNKNOWN\n";
static const char ___i18n_cli_info_001[] = TBC_COMPILER_FULLNAME;

static const tbc_info_txt_st ___i18n_cli_info_txts[] = {
    {sizeof(___i18n_cli_info_000), (char *const)___i18n_cli_info_000},
    {sizeof(___i18n_cli_info_001), (char *const)___i18n_cli_info_001}
};

static const char ___i18n_cli_help_000[] = "3bc -v -i -h -e <prog> -l <linesize> [file]\n";

static const tbc_info_txt_st ___i18n_cli_help_txts[] = {
    {sizeof(___i18n_cli_help_000), (char *const)___i18n_cli_help_000}
};


const tbc_info_txt_st* tbc_i18n_info_arr = ___i18n_cli_info_txts;
const tbc_u8_t tbc_i18n_info_len = sizeof(___i18n_cli_info_txts)/sizeof(tbc_info_txt_st);

const tbc_info_txt_st* tbc_i18n_help_arr = ___i18n_cli_help_txts;
const tbc_u8_t tbc_i18n_help_len = sizeof(___i18n_cli_help_txts)/sizeof(tbc_info_txt_st);
