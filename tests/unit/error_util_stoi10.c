#include <assert.h>
#include <string.h>
#include "util/util_stoi.h"

int main()
{
    {
        tbc_u8_t dest = 248u;
        char* src = "foo";
        assert(util_stoi10(&dest, src, 8, 3) == ERROR_NUMBER_NO_DIGITS);
        assert(dest == 248u);
    }
    {
        tbc_u8_t dest = 198u;
        char* src = "09A";
        assert(util_stoi10(&dest, src, 8, 3) == ERROR_NUMBER_WRONG_BASE);
        assert(dest == 198u);
    }
    {
        tbc_u16_t dest = 10000u;
        char* src = "foo";
        assert(util_stoi10(&dest, src, 16, 3) == ERROR_NUMBER_NO_DIGITS);
        assert(dest == 10000u);
    }
    {
        tbc_u16_t dest = 8000u;
        char* src = "09A";
        assert(util_stoi10(&dest, src, 16, 3) == ERROR_NUMBER_WRONG_BASE);
        assert(dest == 8000u);
    }
    {
        tbc_u32_t dest = 1000000000lu;
        char* src = "foo";
        assert(util_stoi10(&dest, src, 32, 3) == ERROR_NUMBER_NO_DIGITS);
        assert(dest == 1000000000lu);
    }
    {
        tbc_u32_t dest = 800000000lu;
        char* src = "09A";
        assert(util_stoi10(&dest, src, 32, 3) == ERROR_NUMBER_WRONG_BASE);
        assert(dest == 800000000lu);
    }
#if !defined(TBC_NOT_INT64)
    {
        tbc_u64_t dest = 102030405060708090llu;
        char* src = "foo";
        assert(util_stoi10(&dest, src, 64, 3) == ERROR_NUMBER_NO_DIGITS);
        assert(dest == 102030405060708090llu);
    }
    {
        tbc_u64_t dest = 112233445566778899llu;
        char* src = "09A";
        assert(util_stoi10(&dest, src, 64, 3) == ERROR_NUMBER_WRONG_BASE);
        assert(dest == 112233445566778899llu);
    }
#endif
}
