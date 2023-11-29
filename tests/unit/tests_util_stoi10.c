#include <assert.h>
#include <string.h>
#include "util/util_stoi.h"

int main()
{
    {
        tbc_u8_t dest = 42u;
        char src[] = "99";
        assert(util_stoi10(&dest, src, 8, sizeof(src)) == ERROR_UNKNOWN);
        assert(dest == 99);
    }
    {
        tbc_u16_t dest = 4242u;
        char src[] = "9999";
        assert(util_stoi10(&dest, src, 16, sizeof(src)) == ERROR_UNKNOWN);
        assert(dest == 9999u);
    }
    {
        tbc_u32_t dest = 34127856lu;
        char src[]= "99999999";
        assert(util_stoi10(&dest, src, 32, sizeof(src)) == ERROR_UNKNOWN);
        assert(dest == 99999999u);
    }
#if !defined(TBC_NOT_INT64)
    {
        tbc_u64_t dest = 6666666666666666666llu;
        char src[] = "9999999999999999999";
        assert(util_stoi10(&dest, src, 64, sizeof(src)) == ERROR_UNKNOWN);
        assert(dest == 9999999999999999999llu);
    }
#endif
}
