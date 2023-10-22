#include <assert.h>
#include "util/util_ascii.h"

int main()
{
    /** @test case 0: ascii normal caracter */
    {
        char src[] = "'z'";
        assert(util_ascii(src, sizeof(src)) == 'z');
    }
    /** @test case 1: ascii null caracter */
    {
        char src[] = "'\\0'";
        assert(util_ascii(src, sizeof(src)) == 0x0);
    }
    /** @test case 2: ascii bell caracter */
    {
        char src[] = "'\\a'";
        assert(util_ascii(src, sizeof(src)) == 0x7);
    }
    /** @test case 3: ascii tab caracter */     
    {
        char src[] = "'\\t'";
        assert(util_ascii(src, sizeof(src)) == 0x9);
    }
    /** @test case 4: ascii feed line caracter */
    {
        char src[] = "'\\n'";
        assert(util_ascii(src, sizeof(src)) == 0xA);
    }
    /** @test case 5: ascii carrier return caracter */
    {
        char src[] = "'\\r'";
        assert(util_ascii(src, sizeof(src)) == 0x0D);
    }

    return 0;
}
