#include <assert.h>
#include "cast_itos.h"

int main()
{
    {
        char src = 46;
        char dest[64];
        assert(cast_itos2(NULL, &src, 64, 8) == 0);
        assert(cast_itos2(dest, NULL, 64, 8) == 0);
        assert(cast_itos2(dest, &src, 0, 8) == 0);
        assert(cast_itos2(dest, &src, 64, 0) == 0);
        assert(cast_itos2(dest, &src, 64, 65) == 0);
    }
    {
        char src = 46;
        char dest[64];
        char *expected = "101110";
        assert(cast_itos2(dest, &src, 64, 8) == 6);
        assert(strcmp(dest, expected) == 0);
    }
    return 0;
}
