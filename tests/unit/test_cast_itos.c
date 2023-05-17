#include <stdio.h>
#include "cast_itos.h"

int main()
{
    {
        char dest[128];
        const unsigned int src = 12345689U;
        cast_itos10(dest, &src, sizeof(dest), sizeof(src) * 8);
        printf("10: %s\n", dest);
    }
    {
        char dest[128];
        const unsigned int src = 0b101100000000;
        cast_itos2(dest, &src, sizeof(dest), sizeof(src) * 8);
        printf("2: %s\n", dest);
    }
    return 0;
}