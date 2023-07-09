#include <assert.h>
#include "types/types_null.h"
#include "util/util_strchr.h"

int main()
{
    {
        const char* str = "Hello, world!";
        int character = 'o';
        char* result = util_strchr(str, character);
        assert(result != NULL);
        assert(*result == 'o');
    }
    {
        const char* str = "Hello, world!";
        int character = 'z';
        char* result = util_strchr(str, character);
        assert(result == NULL);
    }
    return 0;
}