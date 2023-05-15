#include <stdio.h>
#include "cast_itos.h"

int main()
{
    {
        char dest[128];
        const unsigned int src = 12345689U;
        cast_itos10(dest, &src, sizeof(dest), sizeof(src) * 8);
        printf("%s", dest);
    }
    return 0;
}