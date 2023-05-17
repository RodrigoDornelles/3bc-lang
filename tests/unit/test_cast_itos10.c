#include <assert.h>
#include <string.h>
#include "cast_itos.h"

int main()
{
    {
        char src = 12;
        char dest[21];
        assert(cast_itos10(NULL, &src, 21, 8) == 0);
        assert(cast_itos10(dest, NULL, 21, 8) == 0);
        assert(cast_itos10(dest, &src, 0, 8) == 0);
        assert(cast_itos10(dest, &src, 21, 0) == 0);
        assert(cast_itos10(dest, &src, 21, 9) == 0);
    }
    {
        char src = 12;
        char dest[21];
        char *expected = "12";
        assert(cast_itos10(dest, &src, 21, 8) == 2);
        assert(strcmp(dest, expected) == 0);
    }
    return 0;
}
