#include <assert.h>
#include "types/types_null.h"
#include "util/util_keyword.h"

static tbc_keyword_st keywords[] = {
    {"aldo", 2}, {"erdb", 3}, {"rona", 1}, {"socc", 2}
};

static const int kn = sizeof(keywords)/sizeof(tbc_keyword_st);

int main()
{
    {
        int index = util_keyword(NULL, keywords, kn);
        assert(index == -2);
    }
    {
        char key[] = "aldo";
        int index = util_keyword(key, NULL, kn);
        assert(index == -2);
    }
    {
        char key[] = "rona";
        int index = util_keyword(key, keywords, 0);
        assert(index == -2);
    }
    {
        char key[] = "foot";
        int index = util_keyword(key, keywords, -1);
        assert(index == -2);
    }
    {
        char key[] = "ball";
        int index = util_keyword(key, keywords, kn);
        assert(index == -1);
    }
    return 0;
}