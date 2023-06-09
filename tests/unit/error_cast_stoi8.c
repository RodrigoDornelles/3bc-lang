#include <assert.h>
#include <string.h>
#include "cast_stoi.h"

int main()
{
    {
        tbc_u8_t dest = 34u;
        char* src = "foo";
        assert(cast_stoi8(&dest, src, 8, 3) == ERROR_NUMBER_NO_DIGITS);
        assert(dest == 34u);
    }
    {
        tbc_u8_t dest = 188u;
        char* src = "078";
        assert(cast_stoi8(&dest, src, 8, 3) == ERROR_NUMBER_WRONG_BASE);
        assert(dest == 188u);
    }
    {
        tbc_u16_t dest = 44890u;
        char* src = "foo";
        assert(cast_stoi8(&dest, src, 16, 3) == ERROR_NUMBER_NO_DIGITS);
        assert(dest == 44890u);
    }
    {
        tbc_u16_t dest = 34345u;
        char* src = "078";
        assert(cast_stoi8(&dest, src, 16, 3) == ERROR_NUMBER_WRONG_BASE);
        assert(dest == 34345u);
    }
    {
        tbc_u32_t dest = 1000988000u;
        char* src = "foo";
        assert(cast_stoi8(&dest, src, 32, 3) == ERROR_NUMBER_NO_DIGITS);
        assert(dest == 1000988000u);
    }
    {
        tbc_u32_t dest = 2000000000u;
        char* src = "078";
        assert(cast_stoi8(&dest, src, 32, 3) == ERROR_NUMBER_WRONG_BASE);
        assert(dest == 2000000000u);
    }
    {
        tbc_u64_t dest = 291204129041904091llu;
        char* src = "foo";
        assert(cast_stoi8(&dest, src, 64, 3) == ERROR_NUMBER_NO_DIGITS);
        assert(dest == 291204129041904091llu);
    }
    {
        tbc_u64_t dest = 12345678901234567890llu;
        char* src = "078";
        assert(cast_stoi8(&dest, src, 64, 3) == ERROR_NUMBER_WRONG_BASE);
        assert(dest == 12345678901234567890llu);
    }
}
