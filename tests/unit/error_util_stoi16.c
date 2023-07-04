#include <assert.h>
#include <string.h>
#include "util/util_stoi.h"

int main()
{
    {
        tbc_u8_t dest = 197u;
        char* src = "zoo";
        assert(util_stoi16(&dest, src, 8, 3) == ERROR_NUMBER_NO_DIGITS);
        assert(dest == 197u);
    }
    {
        tbc_u8_t dest = 100u;
        char* src = "FU";
        assert(util_stoi16(&dest, src, 8, 3) == ERROR_NUMBER_WRONG_BASE);
        assert(dest == 100u);
    }
    {
        tbc_u16_t dest = 42069u;
        char* src = "zoo";
        assert(util_stoi16(&dest, src, 16, 3) == ERROR_NUMBER_NO_DIGITS);
        assert(dest == 42069u);
    }
    {
        tbc_u16_t dest = 33333u;
        char* src = "FU";
        assert(util_stoi16(&dest, src, 16, 3) == ERROR_NUMBER_WRONG_BASE);
        assert(dest == 33333u);
    }
    {
        tbc_u32_t dest = 1234567890u;
        char* src = "zoo";
        assert(util_stoi16(&dest, src, 32, 3) == ERROR_NUMBER_NO_DIGITS);
        assert(dest == 1234567890u);
    }
    {
        tbc_u32_t dest = 1231231231u;
        char* src = "FU";
        assert(util_stoi16(&dest, src, 32, 3) == ERROR_NUMBER_WRONG_BASE);
        assert(dest == 1231231231u);
    }
    {
        tbc_u64_t dest = 12899124812414948523llu;
        char* src = "zoo";
        assert(util_stoi16(&dest, src, 64, 3) == ERROR_NUMBER_NO_DIGITS);
        assert(dest == 12899124812414948523llu);
    }
    {
        tbc_u64_t dest = 12345678912345678912llu;
        char* src = "FU";
        assert(util_stoi16(&dest, src, 64, 3) == ERROR_NUMBER_WRONG_BASE);
        assert(dest == 12345678912345678912llu);
    }
    return 0;
}
