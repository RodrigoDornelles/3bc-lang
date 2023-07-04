#include <assert.h>
#include <string.h>
#include "util/util_itos.h"

int main()
{
    {
        char src = 61;
        char dest[16];
        assert(util_itos16(NULL, &src, 16, 8) == 0);
        assert(util_itos16(dest, NULL, 16, 8) == 0);
        assert(util_itos16(dest, &src, 0, 8) == 0);
        assert(util_itos16(dest, &src, 16, 0) == 0);
        assert(util_itos16(dest, &src, 16, 65) == 0);
    }
    {
        int src = 0x3BC;
        char dest[16];
        char *expected = "3BC";
        assert(util_itos16(dest, &src, 16, 16) == 3);
        assert(strcmp(dest, expected) == 0);
    }
    return 0;
}
