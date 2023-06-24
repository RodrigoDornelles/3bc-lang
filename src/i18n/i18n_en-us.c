#define TBC_SOURCE_ENTRY
#include "i18n_en-us.h"

#if !defined(TBC_SCU_OPTIONAL_FIX)

static const char ___tbc_error_000[] = "UNKNOWN ERROR";
static const char ___tbc_error_001[] = "CPU MODE IS NOT DEFINED";
static const char ___tbc_error_002[] = "CPU MODE IS RESERVED";
static const char ___tbc_error_003[] = "INVALID CPU REGISTER";
static const char ___tbc_error_004[] = "INVALID ADDRESS";
static const char ___tbc_error_005[] = "INVALID CONSTANT";
static const char ___tbc_error_006[] = "INVALID CPU MODE";
static const char ___tbc_error_007[] = "INVALID LABEL";
static const char ___tbc_error_008[] = "INVALID PROCEDURE RETURN";
static const char ___tbc_error_009[] = "DUALITY ADDRES WITH VALUE IS NOT ALLOWED";
static const char ___tbc_error_010[] = "VALUE OR ADDRESS IS REQUIRED";
static const char ___tbc_error_011[] = "VALUE IS REQUIRED";
static const char ___tbc_error_012[] = "ADDRESS IS REQUIRED";
static const char ___tbc_error_013[] = "VALUE IS NOT ALLOWED";
static const char ___tbc_error_014[] = "ADDRESS IS NOT ALLOWED";
static const char ___tbc_error_015[] = "NUMBER WITHOUT DIGITS";
static const char ___tbc_error_016[] = "NUMBER UNDERFLOW";
static const char ___tbc_error_017[] = "NUMBER OVERFLOW";
static const char ___tbc_error_018[] = "NUMBER WRONG BASE";
static const char ___tbc_error_019[] = "NEGATIVE NUMBER IS NOT EXPECTED";
static const char ___tbc_error_020[] = "ZERO IS NOT EXPECTED";
static const char ___tbc_error_021[] = "OUT OF MEMORY";
static const char ___tbc_error_022[] = "NONE TTY";
static const char ___tbc_error_023[] = "UNSUPPORTED FEATURE";
static const char ___tbc_error_024[] = "MEMORY CONFIG";
static const char ___tbc_error_025[] = "CANNOT OPEN FILE";
static const char ___tbc_error_026[] = "NULL POINTER";
static const char ___tbc_error_027[] = "INVALID CHARACTER ESCAPE";
static const char ___tbc_error_028[] = "INVALID CHARACTER SIZE";
static const char ___tbc_error_029[] = "WRONG NUMBER OF COLUMNS";
static const char ___tbc_error_030[] = "STACK MEMORY MISSING SIZE";
static const char ___tbc_error_031[] = "STACK MEMORY IS NOT ENOUGH FOR CONFIGURATION";
static const char ___tbc_error_032[] = "STACK MEMORY WAS NOT ENOUGH DURING CONFIGURATION";

static const tbc_error_st ___tbc_errors[] = {
    {sizeof(___tbc_error_000), (char *const)___tbc_error_000},
    {sizeof(___tbc_error_001), (char *const)___tbc_error_001},
    {sizeof(___tbc_error_002), (char *const)___tbc_error_002},
    {sizeof(___tbc_error_003), (char *const)___tbc_error_003},
    {sizeof(___tbc_error_004), (char *const)___tbc_error_004},
    {sizeof(___tbc_error_005), (char *const)___tbc_error_005},
    {sizeof(___tbc_error_006), (char *const)___tbc_error_006},
    {sizeof(___tbc_error_007), (char *const)___tbc_error_007},
    {sizeof(___tbc_error_008), (char *const)___tbc_error_008},
    {sizeof(___tbc_error_009), (char *const)___tbc_error_009},
    {sizeof(___tbc_error_010), (char *const)___tbc_error_010},
    {sizeof(___tbc_error_011), (char *const)___tbc_error_011},
    {sizeof(___tbc_error_012), (char *const)___tbc_error_012},
    {sizeof(___tbc_error_013), (char *const)___tbc_error_013},
    {sizeof(___tbc_error_014), (char *const)___tbc_error_014},
    {sizeof(___tbc_error_015), (char *const)___tbc_error_015},
    {sizeof(___tbc_error_016), (char *const)___tbc_error_016},
    {sizeof(___tbc_error_017), (char *const)___tbc_error_017},
    {sizeof(___tbc_error_018), (char *const)___tbc_error_018},
    {sizeof(___tbc_error_019), (char *const)___tbc_error_019},
    {sizeof(___tbc_error_020), (char *const)___tbc_error_020},
    {sizeof(___tbc_error_021), (char *const)___tbc_error_021},
    {sizeof(___tbc_error_022), (char *const)___tbc_error_022},
    {sizeof(___tbc_error_023), (char *const)___tbc_error_023},
    {sizeof(___tbc_error_024), (char *const)___tbc_error_024},
    {sizeof(___tbc_error_025), (char *const)___tbc_error_025},
    {sizeof(___tbc_error_026), (char *const)___tbc_error_026},
    {sizeof(___tbc_error_027), (char *const)___tbc_error_027},
    {sizeof(___tbc_error_028), (char *const)___tbc_error_028},
    {sizeof(___tbc_error_029), (char *const)___tbc_error_029},
    {sizeof(___tbc_error_030), (char *const)___tbc_error_030},
    {sizeof(___tbc_error_031), (char *const)___tbc_error_031},
    {sizeof(___tbc_error_032), (char *const)___tbc_error_032},
};

const tbc_error_st* tbc_i18n_error_arr = ___tbc_errors;
const tbc_u8_t tbc_i18n_error_len = sizeof(___tbc_errors)/sizeof(tbc_error_st);

#endif
