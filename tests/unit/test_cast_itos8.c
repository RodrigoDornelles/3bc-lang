#include <assert.h>
#include <string.h>
#include "cast_itos.h"

int main()
{
    {
        char src = 0x12;
        char dest[22];
        assert(cast_itos8(NULL, &src, 16, 8) == 0);
        assert(cast_itos8(dest, NULL, 16, 8) == 0);
        assert(cast_itos8(dest, &src, 0, 8) == 0);
        assert(cast_itos8(dest, &src, 16, 0) == 0);
        assert(cast_itos8(dest, &src, 16, 65) == 0);
    }
    {
        char src = 0x12;
        char dest[22];
        char *expected = "22";
        assert(cast_itos8(dest, &src, 16, 8) == 2);
        assert(strcmp(dest, expected) == 0);
    }
    return 0;
}
