#include <assert.h>
#include <string.h>
#include "types/types_null.h"
#include "util/util_dsl.h"

int main()
{
    {
        char src[] = "          ";
        char* dest[10];
        unsigned char destn[sizeof(dest)/sizeof(*dest)];
        int tokens = util_dsl_split(dest, destn, src, sizeof(dest)/sizeof(*dest), sizeof(src));
        assert(tokens == 0);
    }
    {
        char src[] = "..........";
        char* dest[10];
        unsigned char destn[sizeof(dest)/sizeof(*dest)];
        int tokens = util_dsl_split(dest, destn, src, sizeof(dest)/sizeof(*dest), sizeof(src));
        assert(tokens == 0);
    }
    {
        char src[] = " . . . . .";
        char* dest[10];
        unsigned char destn[sizeof(dest)/sizeof(*dest)];
        int tokens = util_dsl_split(dest, destn, src, sizeof(dest)/sizeof(*dest), sizeof(src));
        assert(tokens == 0);
    }
    {
        char src[] = "foo bar baz zig zag zum";
        char* dest[10];
        unsigned char destn[sizeof(dest)/sizeof(*dest)];
        int tokens = util_dsl_split(dest, destn, src, sizeof(dest)/sizeof(*dest), sizeof(src));
        assert(tokens == 6);
        assert(destn[0] == 3);
        assert(destn[1] == 3);
        assert(destn[2] == 3);
        assert(destn[3] == 3);
        assert(destn[4] == 3);
        assert(destn[5] == 3);
        assert(strncmp(dest[0], "foo", destn[0]) == 0);
        assert(strncmp(dest[1], "bar", destn[1]) == 0);
        assert(strncmp(dest[2], "baz", destn[2]) == 0);
        assert(strncmp(dest[3], "zig", destn[3]) == 0);
        assert(strncmp(dest[4], "zag", destn[4]) == 0);
        assert(strncmp(dest[5], "zum", destn[5]) == 0);
    }
    {
        char src[] = "one.two.three.four.five";
        char* dest[5];
        unsigned char destn[sizeof(dest)/sizeof(*dest)];
        int tokens = util_dsl_split(dest, destn, src, sizeof(dest)/sizeof(*dest), sizeof(src));
        assert(tokens == 5);
        assert(destn[0] == 3);
        assert(destn[1] == 3);
        assert(destn[2] == 5);
        assert(destn[3] == 4);
        assert(destn[4] == 4);
        assert(strncmp(dest[0], "one", destn[0]) == 0);
        assert(strncmp(dest[1], "two", destn[1]) == 0);
        assert(strncmp(dest[2], "three", destn[2]) == 0);
        assert(strncmp(dest[3], "four", destn[3]) == 0);
        assert(strncmp(dest[4], "five", destn[4]) == 0);
    }
    {
        char src[] = "one \"two three\" four";
        char* dest[5];
        unsigned char destn[sizeof(dest)/sizeof(*dest)];
        int tokens = util_dsl_split(dest, destn, src, sizeof(dest)/sizeof(*dest), sizeof(src));
        assert(tokens == 3);
        assert(destn[0] == 3);
        assert(destn[1] == 11);
        assert(destn[2] == 4);
        assert(strncmp(dest[0], "one", destn[0]) == 0);
        assert(strncmp(dest[1], "\"two three\"", destn[1]) == 0);
        assert(strncmp(dest[2], "four", destn[2]) == 0);
    }
    {
        char src[] = "one two \"three four\"";
        char* dest[3];
        unsigned char destn[sizeof(dest)/sizeof(*dest)];
        int tokens = util_dsl_split(dest, destn, src, sizeof(dest)/sizeof(*dest), sizeof(src));
        assert(tokens == 3);
        assert(destn[0] == 3);
        assert(destn[1] == 3);
        assert(destn[2] == 12);
        assert(strncmp(dest[0], "one", destn[0]) == 0);
        assert(strncmp(dest[1], "two", destn[1]) == 0);
        assert(strncmp(dest[2], "\"three four\"", destn[2]) == 0);
    }
    {
        char src[] = "\"one two\" three four";
        char* dest[3];
        unsigned char destn[sizeof(dest)/sizeof(*dest)];
        int tokens = util_dsl_split(dest, destn, src, sizeof(dest)/sizeof(*dest), sizeof(src));
        assert(tokens == 3);
        assert(destn[0] == 9);
        assert(destn[1] == 5);
        assert(destn[2] == 4);
        assert(strncmp(dest[0], "\"one two\"", destn[0]) == 0);
        assert(strncmp(dest[1], "three", destn[1]) == 0);
        assert(strncmp(dest[2], "four", destn[2]) == 0);
    }

    return 0;
}