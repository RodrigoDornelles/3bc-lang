#include "i18n_0000.h"
#include "types/types_null.h"

static const char ___i18n_cli_help_000[] = "usage: 3bc [file]\n";
static const char ___i18n_cli_help_001[] = "\t-e <text> evaluate program\n";
static const char ___i18n_cli_help_002[] = "\t-l <size> line max length\n";
static const char ___i18n_cli_help_003[] = "\t-v -V     version (extra)\n";
static const char ___i18n_cli_help_004[] = "\t-i -I     vm info (after)\n";
static const char ___i18n_cli_help_005[] = "\t-m        allow heap\n";

static const tbc_info_txt_st ___i18n_cli_help_txts[] = {
    {sizeof(___i18n_cli_help_000), (char *const)___i18n_cli_help_000},
    {sizeof(___i18n_cli_help_001), (char *const)___i18n_cli_help_001},
    {sizeof(___i18n_cli_help_002), (char *const)___i18n_cli_help_002},
    {sizeof(___i18n_cli_help_003), (char *const)___i18n_cli_help_003},
    {sizeof(___i18n_cli_help_004), (char *const)___i18n_cli_help_004},
    {sizeof(___i18n_cli_help_005), (char *const)___i18n_cli_help_005},
    {1, "\n"},
};

const tbc_info_txt_st* tbc_i18n_help_arr = ___i18n_cli_help_txts;
const tbc_u8_t tbc_i18n_help_len = sizeof(___i18n_cli_help_txts)/sizeof(tbc_info_txt_st);
