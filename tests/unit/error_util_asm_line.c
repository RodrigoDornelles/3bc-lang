#include <assert.h>
#include <string.h>
#include "util/util_asm.h"

int main()
{
    /** @test Case 1: Test with an empty line */
    {
        char src[] = "";
        char *beg, *mid, *end;

        tbc_i8_t length = util_asm_line(&beg, &mid, &end, src, sizeof(src));

        assert(length == 0);
        assert(beg == NULL);
        assert(mid == NULL);
        assert(end == NULL);
    }

    /** @test Case 2: Test with a line containing only spaces and no comments */
    {
        char src[] = "            ";
        char *beg, *mid, *end;

        tbc_i8_t length = util_asm_line(&beg, &mid, &end, src, sizeof(src));

        assert(length == 0);
        assert(beg == NULL);
        assert(mid == NULL);
        assert(end == NULL);
    }

    /** @test Case 3: Test with a line containing only a period and no comments */
    {
        char src[] = "   .";
        char *beg, *mid, *end;

        tbc_i8_t length = util_asm_line(&beg, &mid, &end, src, sizeof(src));

        assert(length == 0);
        assert(beg == NULL);
        assert(mid == NULL);
        assert(end == NULL);
    }

    /** @test Case 4: missing pointer for @c beg */
    {
        char src[] = "fo;bar.z";
        char *beg, *mid, *end ;
        assert(util_asm_line(NULL, &mid, &end, src, sizeof(src)) == -2);
    }

    /** @test Case 5: missing pointer for @c mid */
    {
        char src[] = "fo;bar.z";
        char *beg, *mid, *end ;
        assert(util_asm_line(&beg, NULL, &end, src, sizeof(src)) == -2);
    }

    /** @test Case 6: missing pointer for @c end */
    {
        char src[] = "fo;bar.z";
        char *beg, *mid, *end ;
        assert(util_asm_line(&beg, &mid, NULL, src, sizeof(src)) == -2);
    }

    /** @test Case 7: missing source string */
    {
        char src[] = "fo;bar.z";
        char *beg, *mid, *end ;
        assert(util_asm_line(&beg, &mid, &end, NULL, sizeof(src)) == -2);
    }

    /** @test Case 8: empty source size */
    {
        char src[] = "fo;bar.z";
        char *beg, *mid, *end ;
        assert(util_asm_line(&beg, &mid, &end, src, 0) == 0);
    }

    return 0;
}