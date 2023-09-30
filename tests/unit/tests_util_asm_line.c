#include <assert.h>
#include <string.h>
#include "util/util_asm.h"

int main()
{
    /** @test case 1: Test with a line containing only instruction content */
    {
        char src[] = "         foo bar zzzzzz";
        char *beg, *mid, *end;

        tbc_i8_t length = util_asm_line(&beg, &mid, &end, src, sizeof(src));

        assert(length == 14);
        assert(strncmp(beg, "foo bar zzzzzz", length) == 0);
        assert(mid == NULL);
        assert(end == &src[23]);
    }

    /** @test Case 2: Test with a line containing instruction content and a comment */
    {
        char src[] = "   . This is a test line ;;;; with a comment";
        char *beg, *mid, *end;

        tbc_i8_t length = util_asm_line(&beg, &mid, &end, src, sizeof(src));

        assert(length == 20);
        assert(strncmp(beg, "This is a test line ", 20) == 0);
        assert(mid != &src[26]);
        assert(strcmp(mid, " with a comment") == 0);
        assert(end == &src[44]);
    }
    
    /** @test Case 3: Test with a line containing only spaces and a comment */
    {
        char src[] = "   ; This is a comment line with spaces";
        char *beg, *mid, *end;

        tbc_i8_t length = util_asm_line(&beg, &mid, &end, src, sizeof(src));

        assert(length == 0);
        assert(beg == NULL);
        assert(mid == &src[4]);
        assert(strcmp(mid, " This is a comment line with spaces") == 0);
        assert(end == &src[39]);
    }

    /** @test Case 5: Test with a line containing a comment with no instruction content */
    {
        char src[] = "   ; This is a comment line";
        char *beg, *mid, *end;

        tbc_i8_t length = util_asm_line(&beg, &mid, &end, src, sizeof(src));

        assert(length == 0);
        assert(beg == NULL);
        assert(mid == &src[4]);
        assert(strcmp(mid, " This is a comment line") == 0);
        assert(end == &src[27]);
    }


    /** @test Case 6: Test with a line containing multiple comments */
    {
        char src[] = "   ; Comment 1 ; Comment 2 ; Comment 3";
        char *beg, *mid, *end;

        tbc_i8_t length = util_asm_line(&beg, &mid, &end, src, sizeof(src));

        assert(length == 0);
        assert(beg == NULL);
        assert(mid == &src[4]);
        assert(strcmp(mid, " Comment 1 ; Comment 2 ; Comment 3") == 0);
        assert(end != NULL);
    }


    /** @test Case 7: Test with a line containing a single character instruction and no comments */
    {
        char src[] = "   a";
        char *beg, *mid, *end;

        tbc_i8_t length = util_asm_line(&beg, &mid, &end, src, sizeof(src));

        assert(length == 1);
        assert(strcmp(beg, "a") == 0);
        assert(mid == NULL);
        assert(end == &src[4]);
    }

    return 0;
}