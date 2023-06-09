#include <assert.h>
#include <string.h>
#include "cast_stoi.h"

int main()
{
    {
        tbc_u8_t dest = 85u;
        char* src = "foo";
        assert(cast_stoi2(&dest, src, 8, 3) == ERROR_NUMBER_NO_DIGITS);
        assert(dest == 85u);
    }
    {
        tbc_u8_t dest = 174u;
        char* src = "012";
        assert(cast_stoi2(&dest, src, 8, 3) == ERROR_NUMBER_WRONG_BASE);
        assert(dest == 174u);
    }
    {
        tbc_u16_t dest = 1524u;
        char* src = "foo";
        assert(cast_stoi2(&dest, src, 16, 3) == ERROR_NUMBER_NO_DIGITS);
        assert(dest == 1524u);
    }
    {
        tbc_u16_t dest = 2589u;
        char* src = "012";
        assert(cast_stoi2(&dest, src, 16, 3) == ERROR_NUMBER_WRONG_BASE);
        assert(dest == 2589u);
    }
    {
        tbc_u32_t dest = 1500000000u;
        char* src = "foo";
        assert(cast_stoi2(&dest, src, 32, 3) == ERROR_NUMBER_NO_DIGITS);
        assert(dest == 1500000000u);
    }
    {
        tbc_u32_t dest = 88888888lu;
        char* src = "012";
        assert(cast_stoi2(&dest, src, 32, 3) == ERROR_NUMBER_WRONG_BASE);
        assert(dest == 88888888lu);
    }
    {
        tbc_u64_t dest = 9223372036854775808llu;
        char* src = "foo";
        assert(cast_stoi2(&dest, src, 64, 3) == ERROR_NUMBER_NO_DIGITS);
        assert(dest == 9223372036854775808llu);
    }
    {
        tbc_u64_t dest = 8500000000llu;
        char* src = "012";
        assert(cast_stoi2(&dest, src, 64, 3) == ERROR_NUMBER_WRONG_BASE);
        assert(dest == 8500000000llu);
    }
}
