#include <assert.h>
#include <string.h>
#include "util/util_djb2.h"

int main()
{
    {
        tbc_u8_t dest = 1u;
        char* src = "";
        assert(util_djb2(&dest, src, 8, sizeof(src)) == ERROR_NUMBER_NO_DIGITS);
        assert(dest == 1u);
    }
    {
        tbc_u8_t dest = 22u;
        char* src = "\n";
        assert(util_djb2(&dest, src, 8, sizeof(src)) == ERROR_NUMBER_NO_DIGITS);
        assert(dest == 22u);
    }
    {
        tbc_u16_t dest = 333u;
        char* src = "";
        assert(util_djb2(&dest, src, 16, sizeof(src)) == ERROR_NUMBER_NO_DIGITS);
        assert(dest == 333u);
    }
    {
        tbc_u16_t dest = 4444u;
        char* src = "\n";
        assert(util_djb2(&dest, src, 16, sizeof(src)) == ERROR_NUMBER_NO_DIGITS);
        assert(dest == 4444u);
    }
    {
        tbc_u32_t dest = 55555u;
        char* src = "";
        assert(util_djb2(&dest, src, 32, sizeof(src)) == ERROR_NUMBER_NO_DIGITS);
        assert(dest == 55555u);
    }
    {
        tbc_u32_t dest = 666666lu;
        char* src = "\n";
        assert(util_djb2(&dest, src, 32, sizeof(src)) == ERROR_NUMBER_NO_DIGITS);
        assert(dest == 666666lu);
    }
    {
        tbc_u64_t dest = 7777777llu;
        char* src = "";
        assert(util_djb2(&dest, src, 64, sizeof(src)) == ERROR_NUMBER_INVALID_BASE);
        assert(dest == 7777777llu);
    }
}
