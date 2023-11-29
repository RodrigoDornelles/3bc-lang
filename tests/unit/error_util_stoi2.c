#include <assert.h>
#include <string.h>
#include "util/util_stoi.h"

int main()
{
    {
        tbc_u8_t dest = 44u;
        char* src = "10";
        assert(util_stoi2(&dest, src, 8, 0) == ERROR_NUMBER_NO_DIGITS);
        assert(dest == 44u);
    }
    {
        tbc_u8_t dest = 85u;
        char* src = "";
        assert(util_stoi2(&dest, src, 8, 3) == ERROR_NUMBER_NO_DIGITS);
        assert(dest == 85u);
    }
    {
        tbc_u8_t dest = 174u;
        char* src = "012";
        assert(util_stoi2(&dest, src, 8, 3) == ERROR_NUMBER_WRONG_BASE);
        assert(dest == 174u);
    }
    {
        tbc_u8_t dest = 179u;
        char src[] = "1111111";
        assert(util_stoi2(&dest, src, 6, sizeof(src)) == ERROR_NUMBER_OVERFLOW);
        assert(dest == 179u);
    }
    {
        tbc_u16_t dest = 1234u;
        char* src = "11";
        assert(util_stoi2(&dest, src, 16, 0) == ERROR_NUMBER_NO_DIGITS);
        assert(dest == 1234u);
    }
    {
        tbc_u16_t dest = 1524u;
        char* src = "";
        assert(util_stoi2(&dest, src, 16, 3) == ERROR_NUMBER_NO_DIGITS);
        assert(dest == 1524u);
    }
    {
        tbc_u16_t dest = 2589u;
        char* src = "012";
        assert(util_stoi2(&dest, src, 16, 3) == ERROR_NUMBER_WRONG_BASE);
        assert(dest == 2589u);
    }
    {
        tbc_u16_t dest = 333u;
        char src[] = "111111111111111";
        assert(util_stoi2(&dest, src, 14, sizeof(src)) == ERROR_NUMBER_OVERFLOW);
        assert(dest == 333u);
    }
    {
        tbc_u32_t dest = 1600000000u;
        char* src = "101";
        assert(util_stoi2(&dest, src, 32, 0) == ERROR_NUMBER_NO_DIGITS);
        assert(dest == 1600000000u);
    }
    {
        tbc_u32_t dest = 1500000000u;
        char* src = "";
        assert(util_stoi2(&dest, src, 32, 3) == ERROR_NUMBER_NO_DIGITS);
        assert(dest == 1500000000u);
    }
    {
        tbc_u32_t dest = 88888888lu;
        char* src = "012";
        assert(util_stoi2(&dest, src, 32, 3) == ERROR_NUMBER_WRONG_BASE);
        assert(dest == 88888888lu);
    }
    {
        tbc_u32_t dest = 1500000000lu;
        char src[] = "1111111111111111111111111111111";
        assert(util_stoi2(&dest, src, 30, sizeof(src)) == ERROR_NUMBER_OVERFLOW);
        assert(dest == 1500000000lu);
    }
#if !defined(TBC_NOT_INT64)
    {
        tbc_u64_t dest = 9223492892482944892llu;
        char* src = "111";
        assert(util_stoi2(&dest, src, 64, 0) == ERROR_NUMBER_NO_DIGITS);
        assert(dest == 9223492892482944892llu);
    }
    {
        tbc_u64_t dest = 9223372036854775808llu;
        char* src = "";
        assert(util_stoi2(&dest, src, 64, 3) == ERROR_NUMBER_NO_DIGITS);
        assert(dest == 9223372036854775808llu);
    }
    {
        tbc_u64_t dest = 8500000000llu;
        char* src = "012";
        assert(util_stoi2(&dest, src, 64, 3) == ERROR_NUMBER_WRONG_BASE);
        assert(dest == 8500000000llu);
    }
    
    {
        tbc_u64_t dest = 9223372036852349038llu;
        char src[] = "111111111111111111111111111111111111111111111111111111111111111";
        assert(util_stoi2(&dest, src, 62, sizeof(src)) == ERROR_NUMBER_OVERFLOW);
        assert(dest == 9223372036852349038llu);
    }
    {
        tbc_u64_t dest[2] = {9223372032403940943llu, 9223372032403924244llu};
        char src[] = "111111111111111111111111111111111111111111111111111111111111111";
        assert(util_stoi2(dest, src, 128, sizeof(src)) == ERROR_NUMBER_SIZE_TOO_LONG);
        assert(dest[0] == 9223372032403940943llu);
        assert(dest[1] == 9223372032403924244llu);
    }
#endif
}
