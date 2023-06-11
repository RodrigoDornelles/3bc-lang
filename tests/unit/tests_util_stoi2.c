#include <assert.h>
#include <string.h>
#include "util_stoi.h"

int main()
{
    {
        tbc_u8_t dest = 25u;
        char* src = "01100110";
        assert(util_stoi2(&dest, src, 8, 8) == ERROR_UNKNOWN);
        assert(dest == 0x66);
    }
    {
        tbc_u16_t dest = 25042u;
        char* src = "0110011001100110";
        assert(util_stoi2(&dest, src, 16, 16) == ERROR_UNKNOWN);
        assert(dest == 0x6666);
    }
    {
        tbc_u32_t dest = 20230425lu;
        char* src = "11001100110011001100110011001100";
        assert(util_stoi2(&dest, src, 32, 32) == ERROR_UNKNOWN);
        assert(dest == 0xCCCCCCCC);
    }
    {
        tbc_u64_t dest = 999999999999999999llu;
        char* src = "1010101010101010101010101010101010101010101010101010101010101010";
        assert(util_stoi2(&dest, src, 64, 64) == ERROR_UNKNOWN);
        assert(dest == 0xAAAAAAAAAAAAAAAA);
    }
}
