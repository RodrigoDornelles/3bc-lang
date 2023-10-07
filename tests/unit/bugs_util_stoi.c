#include <assert.h>
#include "util/util_stoi.h"

int main()
{
    {
        tbc_u16_t dest = 33u;
        char src[] = "B__________0";
        assert(util_stoi16(&dest, src, 16, sizeof(src)) == ERROR_UNKNOWN);
        assert(dest == 0xB0);
    }
    {
        tbc_u16_t dest = 44u;
        char src[] = "A_______B_______C";
        assert(util_stoi16(&dest, src, 16, sizeof(src)) == ERROR_UNKNOWN);
        assert(dest == 0x0ABC);
    }
    return 0;
}
