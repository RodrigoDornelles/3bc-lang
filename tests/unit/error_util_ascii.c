#include <assert.h>
#include "util/util_ascii.h"

int main()
{
    /** @test case 0: Empty string should return 0x15 (NACK) */
    {
        char src[] = "";
        assert(util_ascii(src, sizeof(src)) == 0x15);
    }
    /** @test case 1: String that does not start with a single quote should return 0x15 (NACK) */
    {
        char src[] = "z'";
        assert(util_ascii(src, sizeof(src)) == 0x15);
    }
    /** @test case 2: String starting with a single quote but too short to contain a valid character should return 0x15 (NACK) */
    {
        char src[] = "''";
        assert(util_ascii(src, sizeof(src)) == 0x15);
    }
    /** @test case 3: String starting with a single quote and containing an invalid special character should return 0x15 (NACK) */
    {
        char src[] = {'\'', 0x80, '\'', 0x00};
        assert(util_ascii(src, sizeof(src)) == 0x15);
    }
    /** @test case 4: String starting with a single quote and containing an invalid escape sequence should return 0x15 (NACK) */
    {
        char src[] = "'\\x'";
        assert(util_ascii(src, sizeof(src)) == 0x15);
    }
    /** @test case 5: String with an incomplete escape sequence should return 0x15 (NACK) */
    {
        char src[] = "'\\'";
        assert(util_ascii(src, sizeof(src)) == 0x15);
    }

    return 0;
}
