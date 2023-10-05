#include <assert.h>
#include "types/types_null.h"
#include "util/util_asm.h"

int main()
{
    {
        char src[] = "foo bar baz zig zag zum";
        char* dest[5];
        unsigned char destn[sizeof(dest)/sizeof(*dest)];
        assert(util_asm_split(dest, destn, src, sizeof(dest)/sizeof(*dest), sizeof(src)) == -1);
    }
    {
        char src[] = "";
        char* dest[5];
        unsigned char destn[sizeof(dest)/sizeof(*dest)];
        assert(util_asm_split(NULL, destn, src, sizeof(dest)/sizeof(*dest), sizeof(src)) == -2);
    }
    {
        char src[] = "";
        char* dest[5];
        unsigned char destn[sizeof(dest)/sizeof(*dest)];
        assert(util_asm_split(src, NULL, src, sizeof(dest)/sizeof(*dest), sizeof(src)) == -2);
    }
    {
        char src[] = "";
        char* dest[5];
        unsigned char destn[sizeof(dest)/sizeof(*dest)];
        assert(util_asm_split(dest, destn, NULL, sizeof(dest)/sizeof(*dest), sizeof(src)) == -2);
    }
    {
        char src[] = "";
        char* dest[5];
        unsigned char destn[sizeof(dest)/sizeof(*dest)];
        assert(util_asm_split(dest, destn, src, 0, sizeof(src)) == -2);
    }
    {
        char src[] = "";
        char* dest[5];
        unsigned char destn[sizeof(dest)/sizeof(*dest)];
        assert(util_asm_split(dest, destn, src, sizeof(dest)/sizeof(*dest), 0) == -2);
    }
    {
        char src[] = "foo bar \"baz";
        char* dest[5];
        unsigned char destn[sizeof(dest)/sizeof(*dest)];
        assert(util_asm_split(dest, destn, src, sizeof(dest)/sizeof(*dest), sizeof(src)) == -3);
    }
    {
        char src[] = "\"";
        char* dest[5];
        unsigned char destn[sizeof(dest)/sizeof(*dest)];
        assert(util_asm_split(dest, destn, src, sizeof(dest)/sizeof(*dest), sizeof(src)) == -3);
    }

    return 0;
}
