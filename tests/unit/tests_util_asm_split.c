#include <assert.h>
#include <string.h>
#include "types/types_null.h"
#include "util/util_asm.h"

int main()
{
    {
        char src[] = "          ";
        char* dest[10];
        int tokens = util_asm_split(dest, src, sizeof(dest)/sizeof(*dest), sizeof(src));
        assert(tokens == 0);
    }
    {
        char src[] = "..........";
        char* dest[10];
        int tokens = util_asm_split(dest, src, sizeof(dest)/sizeof(*dest), sizeof(src));
        assert(tokens == 0);
    }
    {
        char src[] = " . . . . .";
        char* dest[10];
        int tokens = util_asm_split(dest, src, sizeof(dest)/sizeof(*dest), sizeof(src));
        assert(tokens == 0);
    }
    {
        char src[] = "foo bar baz zig zag zum";
        char* dest[10];
        int tokens = util_asm_split(dest, src, sizeof(dest)/sizeof(*dest), sizeof(src));
        assert(tokens == 6);
        assert(strncmp(dest[0], "foo", 3lu) == 0);
        assert(strncmp(dest[1], "bar", 3lu) == 0);
        assert(strncmp(dest[2], "baz", 3lu) == 0);
        assert(strncmp(dest[3], "zig", 3lu) == 0);
        assert(strncmp(dest[4], "zag", 3lu) == 0);
        assert(strncmp(dest[5], "zum", 3lu) == 0);
    }
    {
        char src[] = "one.two.three.four.five";
        char* dest[5];
        int tokens = util_asm_split(dest, src, sizeof(dest)/sizeof(*dest), sizeof(src));
        assert(tokens == 5);
        assert(strncmp(dest[0], "one", 3lu) == 0);
        assert(strncmp(dest[1], "two", 3lu) == 0);
        assert(strncmp(dest[2], "three", 5lu) == 0);
        assert(strncmp(dest[3], "four", 4lu) == 0);
        assert(strncmp(dest[4], "five", 4lu) == 0);
    }
    {
        char src[] = "one \"two three\" four";
        char* dest[5];
        int tokens = util_asm_split(dest, src, sizeof(dest)/sizeof(*dest), sizeof(src));
        assert(tokens == 3);
        assert(strncmp(dest[0], "one", 3lu) == 0);
        assert(strncmp(dest[1], "\"two three\"", 9lu) == 0);
        assert(strncmp(dest[2], "four", 4lu) == 0);
    }
    {
        char src[] = "one two \"three four\"";
        char* dest[3];
        int tokens = util_asm_split(dest, src, sizeof(dest)/sizeof(*dest), sizeof(src));
        assert(tokens == 3);
        assert(strncmp(dest[0], "one", 3lu) == 0);
        assert(strncmp(dest[1], "two", 3lu) == 0);
        assert(strncmp(dest[2], "\"three four\"", 12lu) == 0);
    }
    {
        char src[] = "\"one two\" three four";
        char* dest[3];
        int tokens = util_asm_split(dest, src, sizeof(dest)/sizeof(*dest), sizeof(src));
        assert(tokens == 3);
        assert(strncmp(dest[0], "\"one two\"", 9u) == 0);
        assert(strncmp(dest[1], "three", 3lu) == 0);
        assert(strncmp(dest[2], "four", 4lu) == 0);
    }

    return 0;
}