#include <assert.h>
#include <string.h>
#include "cast_stoi.h"

int main()
{
    {
        tbc_u8_t dest = 88u;
        char src[] = "77";
        assert(cast_stoi8(&dest, src, 8, sizeof(src)) == ERROR_UNKNOWN);
        assert(dest == 0x3F);
    }
    {
        tbc_u16_t dest = 2727u;
        char src[] = "2777";
        assert(cast_stoi8(&dest, src, 16, sizeof(src)) == ERROR_UNKNOWN);
        assert(dest == 0x5FF);
    }
    {
        tbc_u32_t dest = 1234567lu;
        char src[]= "7654321";
        assert(cast_stoi8(&dest, src, 32, sizeof(src)) == ERROR_UNKNOWN);
        assert(dest == 0x1f58d1);
    }
    {
        tbc_u64_t dest = 888888888888888888llu;
        char src[] = "707070707070707070707";
        assert(cast_stoi8(&dest, src, 64, sizeof(src)) == ERROR_UNKNOWN);
        assert(dest == 0x71c71c71c71c71c7);
    }
}
