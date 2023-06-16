#include <assert.h>
#include <string.h>
#include "util_djb2.h"

int main()
{
    {
        tbc_u8_t dest = 8u;
        char src[] = "password";
        assert(util_djb2(&dest, src, 8, sizeof(src)) == ERROR_UNKNOWN);
        assert(dest == 0x38);
    }
    {
        tbc_u16_t dest = 61u;
        char src[] = "password";
        assert(util_djb2(&dest, src, 16, sizeof(src)) == ERROR_UNKNOWN);
        assert(dest == 0xdc38);
    }
    {
        tbc_u32_t dest = 23u;
        char src[] = "password";
        assert(util_djb2(&dest, src, 32, sizeof(src)) == ERROR_UNKNOWN);
        assert(dest == 0x17f6dc38);
    }
    return 0;
}
