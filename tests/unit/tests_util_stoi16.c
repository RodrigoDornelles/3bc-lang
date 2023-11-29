#include <assert.h>
#include <string.h>
#include "util/util_stoi.h"

int main()
{
    {
        tbc_u8_t dest = 11u;
        char src[] = "BA";
        assert(util_stoi16(&dest, src, 8, sizeof(src)) == ERROR_UNKNOWN);
        assert(dest == 0xBA);
    }
    {
        tbc_u16_t dest = 104u;
        char src[] = "03BC";
        assert(util_stoi16(&dest, src, 16, sizeof(src)) == ERROR_UNKNOWN);
        assert(dest == 0x3BC);
    }
    {
        tbc_u32_t dest = 7654321lu;
        char src[]= "BABACA00";
        assert(util_stoi16(&dest, src, 32, sizeof(src)) == ERROR_UNKNOWN);
        assert(dest == 0xBABACA00);
    }
#if !defined(TBC_NOT_INT64)
    {
        tbc_u64_t dest = 666666666666666666llu;
        char src[] = "CAFECAFECAFECAFE";
        assert(util_stoi16(&dest, src, 64, sizeof(src)) == ERROR_UNKNOWN);
        assert(dest == 0xCAFECAFECAFECAFE);
    }
#endif
}
