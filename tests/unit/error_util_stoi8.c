#include <assert.h>
#include <string.h>
#include "util/util_stoi.h"

int main()
{
    {
        tbc_u8_t dest = 34u;
        char* src = "";
        assert(util_stoi8(&dest, src, 8, 3) == ERROR_NUMBER_NO_DIGITS);
        assert(dest == 34u);
    }
    {
        tbc_u8_t dest = 35u;
        char* src = "77";
        assert(util_stoi8(&dest, src, 8, 0) == ERROR_NUMBER_NO_DIGITS);
        assert(dest == 35u);
    }
    {
        tbc_u8_t dest = 188u;
        char* src = "078";
        assert(util_stoi8(&dest, src, 8, 3) == ERROR_NUMBER_WRONG_BASE);
        assert(dest == 188u);
    }
    {
        tbc_u8_t dest = 189u;
        char* src = "77";
        assert(util_stoi8(&dest, src, 5, 2) == ERROR_NUMBER_OVERFLOW);
        assert(dest == 189u);
    }
    {
        tbc_u8_t dest = 190u;
        char* src = "777";
        assert(util_stoi8(&dest, src, 8, 3) == ERROR_NUMBER_OVERFLOW);
        assert(dest == 190u);
    }
    {
        tbc_u16_t dest = 44890u;
        char* src = "";
        assert(util_stoi8(&dest, src, 16, 3) == ERROR_NUMBER_NO_DIGITS);
        assert(dest == 44890u);
    }
    {
        tbc_u16_t dest = 34345u;
        char* src = "078";
        assert(util_stoi8(&dest, src, 16, 3) == ERROR_NUMBER_WRONG_BASE);
        assert(dest == 34345u);
    }
    {
        tbc_u16_t dest = 32325u;
        char* src = "77777";
        assert(util_stoi8(&dest, src, 14, 5) == ERROR_NUMBER_OVERFLOW);
        assert(dest == 32325u);
    }
    {
        tbc_u16_t dest = 32326u;
        char* src = "777777";
        assert(util_stoi8(&dest, src, 16, 6) == ERROR_NUMBER_OVERFLOW);
        assert(dest == 32326u);
    }
    {
        tbc_u32_t dest = 1000988000u;
        char* src = "";
        assert(util_stoi8(&dest, src, 32, 3) == ERROR_NUMBER_NO_DIGITS);
        assert(dest == 1000988000u);
    }
    {
        tbc_u32_t dest = 2000000000u;
        char* src = "078";
        assert(util_stoi8(&dest, src, 32, 3) == ERROR_NUMBER_WRONG_BASE);
        assert(dest == 2000000000u);
    }
    {
        tbc_u32_t dest = 1800000000u;
        char* src = "7777777777";
        assert(util_stoi8(&dest, src, 29, 10) == ERROR_NUMBER_OVERFLOW);
        assert(dest == 1800000000u);
    }
    {
        tbc_u32_t dest = 1800000001u;
        char* src = "777777777777";
        assert(util_stoi8(&dest, src, 32, 12) == ERROR_NUMBER_OVERFLOW);
        assert(dest == 1800000001u);
    }
#if !defined(TBC_NOT_INT64)
    {
        tbc_u64_t dest = 291204129041904091llu;
        char* src = "";
        assert(util_stoi8(&dest, src, 64, 3) == ERROR_NUMBER_NO_DIGITS);
        assert(dest == 291204129041904091llu);
    }
    {
        tbc_u64_t dest = 12345678901234567890llu;
        char* src = "078";
        assert(util_stoi8(&dest, src, 64, 3) == ERROR_NUMBER_WRONG_BASE);
        assert(dest == 12345678901234567890llu);
    }
    {
        tbc_u64_t dest = 23456789012345678901llu;
        char* src = "77777777777777777777";
        assert(util_stoi8(&dest, src, 59, 20) == ERROR_NUMBER_OVERFLOW);
        assert(dest == 23456789012345678901llu);
    }
    {
        tbc_u64_t dest = 23456789012345678902llu;
        char* src = "7777777777777777777777";
        assert(util_stoi8(&dest, src, 64, 22) == ERROR_NUMBER_OVERFLOW);
        assert(dest == 23456789012345678902llu);
    }
#endif
}
